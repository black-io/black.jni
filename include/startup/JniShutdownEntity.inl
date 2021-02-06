#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
	template< const bool (*SHUTDOWN_FUNCTION)( ::JavaVM* ) >
	JniShutdownEntity<SHUTDOWN_FUNCTION>::JniShutdownEntity( Black::DebugName&& debug_name )
		: m_node{ Black::CONSTRUCT_INPLACE, std::move( debug_name ) }
	{
	}
}
}
}
