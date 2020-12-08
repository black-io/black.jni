#pragma once


// Restoring the logging instructions from macro stack.
#if( defined( BLACK_JNI_RESTORE_ISOLATED_LOGS ) )
	#pragma pop_macro( "BLACK_LOG_ASSERT" )
	#pragma pop_macro( "BLACK_LOG_CRITICAL" )
	#pragma pop_macro( "BLACK_LOG_ERROR" )
	#pragma pop_macro( "BLACK_LOG_WARNING" )
	#pragma pop_macro( "BLACK_LOG_INFO" )
	#pragma pop_macro( "BLACK_LOG_VERBOSE" )
	#pragma pop_macro( "BLACK_LOGS_CLOSE" )
#endif
