#include <black/jni.h>


namespace Black
{
inline namespace Jni
{
inline namespace Global
{
inline namespace JniConnections
{
namespace Internal
{
namespace
{
	constexpr const char* LOG_CHANNEL = "Black/Jni/Connection";
}


	const bool JniConnectionInitializer::Initialize( Black::NotNull<JavaVM*> virtual_machine )
	{
		auto& connection = Black::JniConnection::GetInstance();

		CRETD( connection.m_connection != nullptr, false, LOG_CHANNEL, "Double initialization of JNI connection blocked." );

		const auto main_env_result = virtual_machine->GetEnv( reinterpret_cast<void**>( &connection.m_main_environment ), Black::JNI_VERSION );
		CRETE( main_env_result != JNI_OK, false, LOG_CHANNEL, "Failed to acquire the main JNI environment (error: {:08X}).", main_env_result );

		connection.m_connection = virtual_machine;
		EXPECTS( connection.InitializeDetachKey() );
		ENSURES( connection.m_main_environment != nullptr );

		CRETE( !connection.InitializeServices(), false, LOG_CHANNEL, "Failed to initialize JNI services." );
		return true;
	}

	const bool JniConnectionInitializer::Finalize()
	{
		auto& connection = Black::JniConnection::GetInstance();
		CRET( !Black::JniConnection::IsValid(), true );

		connection.FinalizeServices();
		pthread_key_delete( connection.m_thread_detach_key );

		connection.m_connection			= nullptr;
		connection.m_main_environment	= nullptr;
		connection.m_main_thread_id		= 0;
		connection.m_thread_detach_key	= 0;

		return true;
	}
}
}
}
}
}
