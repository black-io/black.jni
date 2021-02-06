#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
	template< const bool (*STARTUP_FUNCTION)( ::JavaVM* ) >
	JniStartupEntity<STARTUP_FUNCTION>::JniStartupEntity( Black::DebugName&& debug_name )
		: m_node{ Black::CONSTRUCT_INPLACE, std::move( debug_name ) }
	{
	}
}
}
}
