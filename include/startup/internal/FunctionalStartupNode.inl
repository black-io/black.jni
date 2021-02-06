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
	const bool FunctionalStartupNode<ON_STARTUP_FUNCTION>::OnJniStartup( Black::NotNull<::JavaVM*> virtual_machine ) const
	{
		EXPECTS_DEBUG( ON_STARTUP_FUNCTION != nullptr );
		return ON_STARTUP_FUNCTION( virtual_machine );
	}
}
}
}
}
