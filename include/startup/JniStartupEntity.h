#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
	/**
		@brief	Entry point of JNI session startup.

		Instantiation of this template introduces the given `STARTUP_FUNCTION` as part of JNI session startup.
		Instance of instantiated type introduces new node of JNI session startup process.

		To provide some functionality on JNI session startup for user's system, one should:
		* specify the function with `const bool ( ::JavaVM* )` signature;
		* instantiate the `JniStartupEntity` template with specified function;
		* create the object, with static storage duration, of instantiated type.

		Once the given `STARTUP_FUNCTION` succeeds the invocation, it should return `true` as result.
		On any error the function should return `false`.

		For ex. somewhere in library's global scope `Black::JniStartupEntity<OnStartup> my_startup{ "Startup my system" };`

		@tparam	STARTUP_FUNCTION	The function used to be part of JNI session startup process.
	*/
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
		using StartupNode = Internal::StartupStaticList::Node<Internal::FunctionalStartupNode<STARTUP_FUNCTION>>;

	// Private state.
	private:
		StartupNode m_node; // Hosted startup list node.
	};
}
}
}
