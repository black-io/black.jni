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
		@brief	Part of JNI session startup process.

		This node implements the startup process of JNI session. The given function, used for instantiation this template,
		will be invoked while startup process.
		JNI session startup normally is performed in `JNI_OnLoad` function. It is always performed just after the shared library is loaded.

		There is no some order specified between invocations of different startup nodes. So that the one startup function
		should not rely on the execution of other startup functions.

		@tparam	ON_STARTUP_FUNCTION		The function to be called on JNI session startup.
	*/
	template< const bool (*ON_STARTUP_FUNCTION)( ::JavaVM* ) >
	class FunctionalStartupNode final : public BasicStartupNode
	{
	// Static public interface.
	public:
		// For debugging purposes.
		static inline Black::DebugName GetDebugName() { return "JNI_OnLoad entity."; };

	// Construction and initialization.
	public:
		using BasicStartupNode::BasicStartupNode;

	// Private interface.
	private:
		/// @see	BasicStartupNode::OnJniStartup
		const bool OnJniStartup( Black::NotNull<::JavaVM*> virtual_machine ) const override;

		/// @see	BasicStartupNode::OnJniShutdown
		const bool OnJniShutdown( Black::NotNull<::JavaVM*> virtual_machine ) const override { return true; };
	};
}
}
}
}
