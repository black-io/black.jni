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
		@brief	Interface of JNI startup node.

		Even it named `Startup Node` it consists of two functions, which are called in different time.
		* `OnJniStartup` function will be called just inside of `JNI_OnLoad`.
		* `OnJniShutdown` is called, in opposition, inside of `JNI_OnUnload`.

		Both functions may be considered as not a functions, but like event callbacks, which will be executed on certain conditions in program.

		All this means that the each implementation of `BasicStartupNode` interface will be used at startup and shutdown of global JNI environment.
	*/
	class BasicStartupNode : private Black::NonTransferable
	{
	// Construction and destruction.
	public:
		BasicStartupNode()										= default;
		explicit BasicStartupNode( Black::DebugName&& name )	: m_name{ std::move( name ) } {};
		virtual ~BasicStartupNode()								= default;

	// Public interface.
	public:
		// Event to be executed on `JNI_OnLoad` function.
		virtual const bool OnJniStartup( Black::NotNull<::JavaVM*> virtual_machine ) const = 0;

		// Event to be executed on `JNI_OnUnload` function.
		virtual const bool OnJniShutdown( Black::NotNull<::JavaVM*> virtual_machine ) const = 0;


		// Get the name of this node for debug purposes only.
		inline std::string_view GetName() const { return *m_name; };

	// Private state.
	private:
		Black::DebugName m_name; // Stored name for debug purposes.
	};
}
}
}
}
