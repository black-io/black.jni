#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
	/**
		@brief	Entry point of JNI session shutdown.

		Instantiation of this template introduces the given `SHUTDOWN_FUNCTION` as part of JNI session shutdown.
		Instance of instantiated type introduces new node of JNI session shutdown process.

		To provide some functionality on JNI session shutdown for user's system, one should:
		* specify the function with `const bool ( ::JavaVM* )` signature;
		* instantiate the `JniShutdownEntity` template with specified function;
		* create the object, with static storage duration, of instantiated type.

		Once the given `SHUTDOWN_FUNCTION` succeeds the invocation, it should return `true` as result.
		On any error the function should return `false`.

		For ex. somewhere in library's global scope `Black::JniShutdownEntity<OnShutdown> my_shutdown{ "Shutdown my system" };`

		@tparam	SHUTDOWN_FUNCTION	The function used to be part of JNI session shutdown process.
	*/
	template< const bool (*SHUTDOWN_FUNCTION)( ::JavaVM* ) >
	class JniShutdownEntity final : private Black::NonTransferable
	{
	// Construction and initialization.
	public:
		JniShutdownEntity() = delete;
		explicit JniShutdownEntity( Black::DebugName&& debug_name );

	// Private inner types.
	private:
		// Type of shutdown list node, which will store the shutdown function.
		using ShutdownNode = Internal::StartupStaticList::Node<Internal::FunctionalShutdownNode<SHUTDOWN_FUNCTION>>;

	// Private state.
	private:
		ShutdownNode m_node; // Hosted shutdown list node.
	};
}
}
}
