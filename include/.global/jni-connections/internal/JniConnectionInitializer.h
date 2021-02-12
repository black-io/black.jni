#pragma once


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
	/**
		@brief	Initialization tool for JNI connection instance.

		This tool is used by JNI startup subsystem to initialize the JNI connection properly.
		Also it is used on JNI finalization.
	*/
	class JniConnectionInitializer final : Black::NonTransferable
	{
	// Static public interface.
	public:
		// Initialize the JNI connection. Expected to be used only at `JNI_OnLoad` function.
		static const bool Initialize( Black::NotNull<JavaVM*> virtual_machine );

		// Finalize the JNI connection. Expected to be used only at `JNI_OnUnload` function.
		static const bool Finalize();
	};
}
}
}
}
}
