#include <black.jni.h>
#include <pthread.h>


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
	namespace
	{
		static constexpr const char* LOG_CHANNEL = "Black/Jni/Connection";
	}

	const bool JniConnection::Initialize( Black::NotNull<JavaVM> jvm )
	{
		auto& connection = GetInstance();

		CRETD( connection.m_connection != nullptr, false, LOG_CHANNEL, "Double initialization of JNI connection blocked." );

		const auto main_env_result = jvm->GetEnv( reinterpret_cast<void**>( &connection.m_main_env ), Black::JNI_VERSION );
		CRETM( main_env_result != JNI_OK, false, LOG_CHANNEL, "Failed to acquire the main JNI environment (error: {:08X}).", main_env_result );

		connection.m_connection = jvm;
		EXPECTS( connection.InitEnvDetacher() );
		ENSURES( connection.m_main_env != nullptr );

		CRETM( !connection.m_stored_classes.Initialize(), false, LOG_CHANNEL, "Failed to initialize the shared class storage." );
		CRETM( !connection.AcquireClassInterface(), false, LOG_CHANNEL, "Failed to acquire JNI common class interface." );
		CRETM( !connection.m_cached_states.Initialize(), false, LOG_CHANNEL, "Failed to initialize the shared state cache." );

		return true;
	}

	const bool JniConnection::Finalize()
	{
		auto& connection = GetInstance();
		CRET( !IsValid(), true );

		connection.m_get_simple_name_func		= {};
		connection.m_get_name_func				= {};
		connection.m_get_canonical_name_func	= {};
		connection.m_get_super_class_func		= {};

		connection.m_cached_states.Finalize();
		connection.m_stored_classes.Finalize();

		pthread_key_delete( connection.m_thread_detach_key );

		connection.m_connection			= nullptr;
		connection.m_main_env			= nullptr;
		connection.m_main_thread_id		= 0;
		connection.m_thread_detach_key	= 0;

		return true;
	}

	const bool JniConnection::RegisterClassNatives( const Black::NativeBindingTable& bindings )
	{
		CRETD( !IsValid(), false, LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );

		JNIEnv* local_env = GetLocalEnvironment();
		Black::JniClass bound_class{ bindings.class_name };
		CRETM( !bound_class, false, LOG_CHANNEL, "Failed to get handle to class '{}'.", bindings.class_name );

		std::vector<JNINativeMethod> jni_natives;
		jni_natives.reserve( bindings.natives.size() );
		std::transform(
			bindings.natives.begin(), bindings.natives.end(), std::back_inserter( jni_natives ),
			[]( const Internal::NativeFunction& func )
			{
				return static_cast<JNINativeMethod>( func );
			}
		);

		auto result = local_env->RegisterNatives( *bound_class, jni_natives.data(), static_cast<jsize>( jni_natives.size() ) );
		CRETM( result != JNI_OK, false, LOG_CHANNEL, "Failed to register natives for class '{}', error code: {:08X}", bindings.class_name, result );

		return true;
	}

	const bool JniConnection::RegisterClassNatives( std::initializer_list<Black::NativeBindingTable> bindings )
	{
		using RegisterFunction = const bool (*)( const Black::NativeBindingTable& );

		// Select the right overload for function name.
		return std::all_of( bindings.begin(), bindings.end(), static_cast<RegisterFunction>( JniConnection::RegisterClassNatives ) );
	}

	Black::NotNull<JNIEnv> JniConnection::GetLocalEnvironment()
	{
		ENSURES( IsValid() );

		auto& connection = GetInstance();
		CRET( IsMainThread(), connection.m_main_env );

		JNIEnv* local_env			= nullptr;
		const auto env_result		= connection.m_connection->GetEnv( reinterpret_cast<void**>( &local_env ), Black::JNI_VERSION );
		CRET( env_result == JNI_OK, local_env );

		const auto attach_result	= connection.m_connection->AttachCurrentThread( &local_env, nullptr );
		EXPECTS( attach_result == JNI_OK );

		const auto attached_env		= pthread_getspecific( connection.m_thread_detach_key );
		CRETD( attached_env != nullptr, local_env, LOG_CHANNEL, "Looks like the JNI environment was reattached to {:016X}.", (int64_t)pthread_self() );

		const auto detach_result	= pthread_setspecific( connection.m_thread_detach_key, local_env );
		CRETD( detach_result != 0, local_env, LOG_CHANNEL, "Failed to attach JNI environment to {:016X} (error: {:08X})", (int64_t)pthread_self(), detach_result );

		return local_env;
	}

	const bool JniConnection::IsMainThread()
	{
		return pthread_self() == GetInstance().m_main_thread_id;
	}

	JniConnection& JniConnection::GetInstance()
	{
		static JniConnection connection;
		return connection;
	}

	void JniConnection::DetachLocalEnv( void* local_env )
	{
		ENSURES( IsValid() );
		GetConnection()->DetachCurrentThread();
	}

	std::string JniConnection::GetClassName( const Black::JniClass& class_handle )
	{
		EXPECTS_DEBUG( IsValid() );

		JNIEnv* local_env = GetLocalEnvironment();
		std::string name{ GetInstance().m_get_name_func.Call( local_env, *class_handle ) };

		std::transform( name.begin(), name.end(), name.begin(), []( char& ch ){ return ( ch == '.' )? '/' : ch; } );
		return name;
	}

	std::string JniConnection::GetSimpleClassName( const Black::JniClass& class_handle )
	{
		EXPECTS_DEBUG( IsValid() );

		JNIEnv* local_env = GetLocalEnvironment();
		return GetInstance().m_get_simple_name_func.Call( local_env, *class_handle );
	}

	std::string JniConnection::GetCanonicalClassName( const Black::JniClass& class_handle )
	{
		EXPECTS_DEBUG( IsValid() );

		JNIEnv* local_env = GetLocalEnvironment();
		return GetInstance().m_get_canonical_name_func.Call( local_env, *class_handle );
	}

	JniClass JniConnection::GetParentClass( const Black::JniClass& class_handle )
	{
		EXPECTS_DEBUG( IsValid() );

		JNIEnv* local_env = GetLocalEnvironment();
		return GetInstance().m_get_super_class_func.Call( local_env, *class_handle );
	}

	const bool JniConnection::InitEnvDetacher()
	{
		CRETD( m_main_thread_id != 0, false, LOG_CHANNEL, "Double initialization of environment detacher blocked." );

		m_main_thread_id = pthread_self();

		ENSURES( pthread_key_create( reinterpret_cast<pthread_key_t*>( &m_thread_detach_key ), JniConnection::DetachLocalEnv ) == 0 );

		return true;
	}

	const bool JniConnection::AcquireClassInterface()
	{
		const Black::JniClass class_handle{ "java/lang/Class" };
		CRETM( !class_handle, false, LOG_CHANNEL, "Failed to locate `java.lang.Class` class." );

		m_get_super_class_func = { class_handle, "getSuperclass" };
		CRETM( !m_get_super_class_func, false, LOG_CHANNEL, "Failed to locate `Class Class::getSuperclass()` function." );

		m_get_canonical_name_func = { class_handle, "getCanonicalName" };
		CRETM( !m_get_canonical_name_func, false, LOG_CHANNEL, "Failed to locate `String Class::getCanonicalName()` function." );

		m_get_name_func = { class_handle, "getName" };
		CRETM( !m_get_name_func, false, LOG_CHANNEL, "Failed to locate `String Class::getName()` function." );

		m_get_simple_name_func = { class_handle, "getSimpleName" };
		CRETM( !m_get_simple_name_func, false, LOG_CHANNEL, "Failed to locate `String Class::getSimpleName()` function." );

		return true;
	}
}
}
}
