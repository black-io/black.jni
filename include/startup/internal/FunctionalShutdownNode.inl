#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
namespace Internal
{
	template< const bool (*ON_SHUTDOWN_FUNCTION)( ::JavaVM* ) >
	const bool FunctionalShutdownNode<ON_SHUTDOWN_FUNCTION>::OnJniShutdown( Black::NotNull<::JavaVM*> virtual_machine ) const
	{
		EXPECTS_DEBUG( ON_SHUTDOWN_FUNCTION != nullptr );
		return ON_SHUTDOWN_FUNCTION( virtual_machine );
	}
}
}
}
}
