#define BLACK_JNI_LIBRARY

#include <black/jni.h>
#include <black/jni/startup.h>


namespace
{
	static constexpr const char* LOG_CHANNEL = "Black/Jni";


	using Black::Jni::Startup::Internal::BasicStartupNode;
	using Black::Jni::Startup::Internal::StartupStaticList;
}


extern "C"
{
	JNIEXPORT jint JNI_OnLoad( JavaVM* virtual_machine, void* reserved )
	{
		BLACK_LOG_DEBUG( LOG_CHANNEL, "Attempt to initialize native library." );
		CRETE( !Black::JniConnection::Initialize( virtual_machine ), -1, LOG_CHANNEL, "Failed to initialize jni connection." );

		for( const BasicStartupNode& entity : StartupStaticList{} )
		{
			BLACK_LOG_DEBUG( LOG_CHANNEL, "Perform the initialization for {}.", entity.GetName() );
			CRETE( !entity.OnJniStartup( virtual_machine ), -1, LOG_CHANNEL, "Failed to initialize {}.", entity.GetName() );
		}

		BLACK_LOG_DEBUG( LOG_CHANNEL, "Native library initialized." );
		return Black::JNI_VERSION;
	}

	JNIEXPORT void JNI_OnUnload( JavaVM* virtual_machine, void* reserved )
	{
		BLACK_LOG_DEBUG( LOG_CHANNEL, "Attempt to finalize native library." );
		for( const BasicStartupNode& entity : StartupStaticList{} )
		{
			BLACK_LOG_DEBUG( LOG_CHANNEL, "Perform the finalization for {}.", entity.GetName() );
			entity.OnJniShutdown( virtual_machine );
		}

		Black::JniConnection::Finalize();
		BLACK_LOG_DEBUG( LOG_CHANNEL, "Native library finalized." );
	}
}
