#pragma once

#if( defined( BLACK_JNI_LOGGING_ISOLATION ) )
	#if( defined( BLACK_ISOLATE_LOG_ASSERT ) )
		#pragma pop_macro( "BLACK_LOG_ASSERT" )
		#undef BLACK_ISOLATE_LOG_ASSERT
	#else
		#undef BLACK_LOG_ASSERT
	#endif

	#if( defined( BLACK_ISOLATE_LOG_CRITICAL ) )
		#pragma pop_macro( "BLACK_LOG_CRITICAL" )
		#undef BLACK_ISOLATE_LOG_CRITICAL
	#else
		#undef BLACK_LOG_CRITICAL
	#endif

	#if( defined( BLACK_ISOLATE_LOG_ERROR ) )
		#pragma pop_macro( "BLACK_LOG_ERROR" )
		#undef BLACK_ISOLATE_LOG_ERROR
	#else
		#undef BLACK_LOG_ERROR
	#endif

	#if( defined( BLACK_ISOLATE_LOG_WARNING ) )
		#pragma pop_macro( "BLACK_LOG_WARNING" )
		#undef BLACK_ISOLATE_LOG_WARNING
	#else
		#undef BLACK_LOG_WARNING
	#endif

	#if( defined( BLACK_ISOLATE_LOG_INFO ) )
		#pragma pop_macro( "BLACK_LOG_INFO" )
		#undef BLACK_ISOLATE_LOG_INFO
	#else
		#undef BLACK_LOG_INFO
	#endif

	#if( defined( BLACK_ISOLATE_LOG_VERBOSE ) )
		#pragma pop_macro( "BLACK_LOG_VERBOSE" )
		#undef BLACK_ISOLATE_LOG_VERBOSE
	#else
		#undef BLACK_LOG_VERBOSE
	#endif

	#if( defined( BLACK_ISOLATE_LOG_DEBUG ) )
		#pragma pop_macro( "BLACK_LOG_DEBUG" )
		#undef BLACK_ISOLATE_LOG_DEBUG
	#else
		#undef BLACK_LOG_DEBUG
	#endif

	#if( defined( BLACK_ISOLATE_LOGS_CLOSE ) )
		#pragma pop_macro( "BLACK_LOGS_CLOSE" )
		#undef BLACK_ISOLATE_LOGS_CLOSE
	#else
		#undef BLACK_LOGS_CLOSE
	#endif
#endif
