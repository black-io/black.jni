#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
namespace Internal
{
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
