#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
	template< const bool (*STARTUP_FUNCTION)( ::JavaVM* ) >
	class JniStartupEntity final : private Black::NonTransferable
	{
	// Construction and initialization.
	public:
		JniStartupEntity() = delete;
		JniStartupEntity( Black::DebugName&& debug_name );

	// Private inner types.
	private:
		// Type of startup list node, which will store the startup function.
		using StartupListNode = Internal::StartupStaticList::Node<Internal::FunctionalStartupNode<STARTUP_FUNCTION>>;

	// Private state.
	private:
		StartupListNode m_node; // Hosted startup list node.
	};
}
}
}
