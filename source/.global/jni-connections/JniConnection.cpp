#include <black/jni.h>
#include <black/jni/handles.h>
#include <black/jni/startup.h>

#include <pthread.h>


namespace Black
{
inline namespace Jni
{
inline namespace Global
{
inline namespace JniConnections
{
namespace
{
	// Only at this time. Allow access to internal registry for classes.
	using Black::Jni::Handles::Internal::ClassRegistry;
	using Black::Jni::Handles::Internal::ObjectStateRegistry;


	constexpr const char* LOG_CHANNEL = "Black/Jni/Connection";
}


	const bool JniConnection::RegisterClassNatives( const NativeBindingTable& bindings )
	{
		CRETD( !IsValid(), false, LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );

		JNIEnv* local_env = GetLocalEnvironment();
		Black::JniClass bound_class{ bindings.class_name };
		CRETE( !bound_class, false, LOG_CHANNEL, "Failed to get handle to class '{}'.", bindings.class_name );

		std::vector<JNINativeMethod> jni_natives;
		jni_natives.reserve( bindings.natives.size() );
		std::copy( bindings.natives.begin(), bindings.natives.end(), std::back_inserter( jni_natives ) );

		auto result = local_env->RegisterNatives( *bound_class, jni_natives.data(), static_cast<jsize>( jni_natives.size() ) );
		CRETE( result != JNI_OK, false, LOG_CHANNEL, "Failed to register natives for class '{}', error code: {:08X}", bindings.class_name, result );

		return true;
	}

	const bool JniConnection::RegisterClassNatives( std::initializer_list< NativeBindingTable> bindings )
	{
		using RegisterFunction = const bool (*)( const NativeBindingTable& );

		// Select the right overload for function name.
		return std::all_of( bindings.begin(), bindings.end(), static_cast<RegisterFunction>( JniConnection::RegisterClassNatives ) );
	}

	Black::NotNull<JNIEnv*> JniConnection::GetLocalEnvironment()
	{
		ENSURES( IsValid() );

		auto& connection = GetInstance();
		CRET( IsMainThread(), connection.m_main_environment );

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

	Black::NotNull<jclass> JniConnection::GetClassReference( std::string_view class_path )
	{
		return ClassRegistry::GetLocalClassReference( class_path );
	}

	std::string JniConnection::GetClassName( Black::NotNull<jclass> class_ref )
	{
		return ClassRegistry::GetClassName( class_ref );
	}

	std::string JniConnection::GetSimpleClassName( Black::NotNull<jclass> class_ref )
	{
		return ClassRegistry::GetSimpleClassName( class_ref );
	}

	std::string JniConnection::GetCanonicalClassName( Black::NotNull<jclass> class_ref )
	{
		return ClassRegistry::GetCanonicalClassName( class_ref );
	}

	void JniConnection::NotifyFromObject( Black::NotNull<jobject> object_ref )
	{
		ObjectStateRegistry::NotifyFromObject( object_ref );
	}

	void JniConnection::NotifyAllFromObject( Black::NotNull<jobject> object_ref )
	{
		ObjectStateRegistry::NotifyAllFromObject( object_ref );
	}

	void JniConnection::WaitFromObject( Black::NotNull<jobject> object_ref )
	{
		ObjectStateRegistry::WaitFromObject( object_ref );
	}

	void JniConnection::WaitFromObject( Black::NotNull<jobject> object_ref, const int64_t milliseconds )
	{
		ObjectStateRegistry::WaitFromObject( object_ref, milliseconds );
	}

	void JniConnection::WaitFromObject( Black::NotNull<jobject> object_ref, const int64_t milliseconds, const int32_t nanoseconds )
	{
		ObjectStateRegistry::WaitFromObject( object_ref, milliseconds, nanoseconds );
	}

	const bool JniConnection::IsMainThread()
	{
		return pthread_self() == GetInstance().m_main_thread_id;
	}

	JniConnection& JniConnection::GetInstance()
	{
		return Black::JniSessionStorage::Get<JniConnection>();
	}

	const bool JniConnection::InitializeServices()
	{
		CRETE( !ClassRegistry::GetInstance().Initialize(), false, LOG_CHANNEL, "Failed to initialize the class registry." );
		CRETE( !ObjectStateRegistry::GetInstance().Initialize(), false, LOG_CHANNEL, "Failed to initialize the object-state registry." );

		return true;
	}

	const bool JniConnection::FinalizeServices()
	{
		CRETE( !ObjectStateRegistry::GetInstance().Finalize(), false, LOG_CHANNEL, "Failed to finalize the object-state registry." );
		CRETE( !ClassRegistry::GetInstance().Finalize(), false, LOG_CHANNEL, "Failed to finalize the class registry." );

		return true;
	}

	const bool JniConnection::InitializeDetachKey()
	{
		CRETD( m_main_thread_id != 0, false, LOG_CHANNEL, "Double initialization of environment detacher blocked." );

		m_main_thread_id = pthread_self();

		ENSURES( pthread_key_create( reinterpret_cast<pthread_key_t*>( &m_thread_detach_key ), JniConnection::DetachLocalEnvironment ) == 0 );

		return true;
	}

	void JniConnection::DetachLocalEnvironment( void* local_environment )
	{
		ENSURES( IsValid() );
		BLACK_LOG_DEBUG( LOG_CHANNEL, "Thread-local environment `{:p}` will be detached from thread `#{:X}`.", local_environment, (uint64_t)pthread_self() );
		GetConnection()->DetachCurrentThread();
	}
}
}
}
}
