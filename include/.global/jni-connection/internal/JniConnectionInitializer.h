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
	*/
	class JniConnectionInitializer final : Black::NonTransferable
	{
	// Static public interface.
	public:
		// Initialize the JNI connection. Expected to be used only at `JNI_OnLoad` function.
		static const bool Initialize( Black::NotNull<JavaVM*> jvm );

		// Finalize the JNI connection. Expected to be used only at `JNI_OnUnload` function.
		static const bool Finalize();
	};
}
}
}
}
}
