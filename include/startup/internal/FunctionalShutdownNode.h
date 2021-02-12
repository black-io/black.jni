#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
namespace Internal
{
	/**
		@brief	Part of JNI session shutdown process.

		This node implements the shutdown process of JNI session. The given function, used for instantiation this template,
		will be invoked while shutdown process.
		JNI session shutdown normally is performed in `JNI_OnUnload` function. But the process may be closed without proper shutdown.

		There is no some order specified between invocations of different shutdown nodes. So that the one shutdown function
		should not rely on the execution of other shutdown functions.

		@tparam	ON_SHUTDOWN_FUNCTION	The function to be called on JNI session shutdown.
	*/
	template< const bool (*ON_SHUTDOWN_FUNCTION)( ::JavaVM* ) >
	class FunctionalShutdownNode final : public BasicStartupNode
	{
	// Static public interface.
	public:
		// For debugging purposes.
		static inline Black::DebugName GetDebugName() { return "JNI_OnUnload entity."; };

	// Construction and initialization.
	public:
		using BasicStartupNode::BasicStartupNode;

	// Private interface.
	private:
		/// @see	BasicStartupNode::OnJniStartup
		const bool OnJniStartup( Black::NotNull<::JavaVM*> virtual_machine ) const override { return true; };

		/// @see	BasicStartupNode::OnJniShutdown
		const bool OnJniShutdown( Black::NotNull<::JavaVM*> virtual_machine ) const override;
	};
}
}
}
}
