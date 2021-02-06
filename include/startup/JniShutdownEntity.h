#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
	template< const bool (*SHUTDOWN_FUNCTION)( ::JavaVM* ) >
	class JniShutdownEntity final : private Black::NonTransferable
	{
	// Construction and initialization.
	public:
		JniShutdownEntity() = delete;
		explicit JniShutdownEntity( Black::DebugName&& debug_name );

	// Private inner types.
	private:
		// Type of startup list node, which will store the shutdown function.
		using StartupListNode = Internal::StartupStaticList::Node<Internal::FunctionalShutdownNode<SHUTDOWN_FUNCTION>>;

	// Private state.
	private:
		StartupListNode m_node; // Hosted startup list node.
	};
}
}
}
