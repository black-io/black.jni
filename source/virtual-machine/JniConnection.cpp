#include <black.jni.h>
#include <pthread.h>


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
	static constexpr char LOG_CHANNEL[] = "Black/Jni/Connection";

	const bool JniConnection::Initialize( Black::NotNull<JavaVM> jvm )
	{
		auto& connection = GetInstance();

		CRETD( connection.m_connection != nullptr, false, LOG_CHANNEL, "Double initialization of JNI connection blocked." );

		auto main_env_result = jvm->GetEnv( reinterpret_cast<void**>( connection.m_main_env ), Black::JNI_VERSION );
		CRETM( main_env_result != JNI_OK, false, LOG_CHANNEL, "Failed to acquire the main JNI environment (error: {:08X}).", main_env_result );

		connection.m_connection = jvm;
		EXPECTS( connection.InitEnvDetacher() );
		ENSURES( connection.m_main_env != nullptr );

		CRETM( !connection.m_stored_classes.Initialize(), false, LOG_CHANNEL, "Failed to initialize the shared class storage." );
		CRETM( !connection.m_cached_states.Initialize(), false, LOG_CHANNEL, "Failed to initialize the shared state cache." );

		return true;
	}

	const bool JniConnection::Finalize()
	{
		auto& connection = GetInstance();
		CRET( !IsValid(), true );

		connection.m_cached_states.Finalize();
		connection.m_stored_classes.Finalize();

		pthread_key_delete( connection.m_thread_detach_key );

		connection.m_connection			= nullptr;
		connection.m_main_env			= nullptr;
		connection.m_main_thread_id		= 0;
		connection.m_thread_detach_key	= 0;
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
			[]( const Traits::NativeFunction& func )
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
		const auto env_result		= connection.m_connection->GetEnv( reinterpret_cast<void**>( local_env ), Black::JNI_VERSION );
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

	const bool JniConnection::InitEnvDetacher()
	{
		CRETD( m_main_thread_id != 0, false, LOG_CHANNEL, "Double initialization of environment detacher blocked." );

		m_main_thread_id = pthread_self();

		ENSURES( pthread_key_create( reinterpret_cast<pthread_key_t*>( &m_thread_detach_key ), JniConnection::DetachLocalEnv ) == 0 );

		return true;
	}
}
}
}
