#include <black/jni.h>

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
	static constexpr const char* LOG_CHANNEL = "Black/Jni/Connection";
}


	const bool JniConnection::RegisterClassNatives( const NativeBindingTable& bindings )
	{
		return false;
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

	Black::NotNull<jclass> GetClassReference( std::string_view class_path )
	{
		return { nullptr };
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

	void JniConnection::DetachLocalEnvironment( void* local_environment )
	{
		ENSURES( IsValid() );
		GetConnection()->DetachCurrentThread();
	}

	const bool JniConnection::InitEnvironmentDetacher()
	{
		CRETD( m_main_thread_id != 0, false, LOG_CHANNEL, "Double initialization of environment detacher blocked." );

		m_main_thread_id = pthread_self();

		ENSURES( pthread_key_create( reinterpret_cast<pthread_key_t*>( &m_thread_detach_key ), JniConnection::DetachLocalEnvironment ) == 0 );

		return true;
	}
}
}
}
}
