#pragma once


#if( defined( BLACK_LOG_ASSERT ) )
	#define BLACK_ISOLATE_LOG_ASSERT
	#pragma push_macro( "BLACK_LOG_ASSERT" )
	#undef BLACK_LOG_ASSERT
#endif

#if( defined( BLACK_LOG_CRITICAL ) )
	#define BLACK_ISOLATE_LOG_CRITICAL
	#pragma push_macro( "BLACK_LOG_CRITICAL" )
	#undef BLACK_LOG_CRITICAL
#endif

#if( defined( BLACK_LOG_ERROR ) )
	#define BLACK_ISOLATE_LOG_ERROR
	#pragma push_macro( "BLACK_LOG_ERROR" )
	#undef BLACK_LOG_ERROR
#endif

#if( defined( BLACK_LOG_WARNING ) )
	#define BLACK_ISOLATE_LOG_WARNING
	#pragma push_macro( "BLACK_LOG_WARNING" )
	#undef BLACK_LOG_WARNING
#endif

#if( defined( BLACK_LOG_INFO ) )
	#define BLACK_ISOLATE_LOG_INFO
	#pragma push_macro( "BLACK_LOG_INFO" )
	#undef BLACK_LOG_INFO
#endif

#if( defined( BLACK_LOG_VERBOSE ) )
	#define BLACK_ISOLATE_LOG_VERBOSE
	#pragma push_macro( "BLACK_LOG_VERBOSE" )
	#undef BLACK_LOG_VERBOSE
#endif

#if( defined( BLACK_LOG_DEBUG ) )
	#define BLACK_ISOLATE_LOG_DEBUG
	#pragma push_macro( "BLACK_LOG_DEBUG" )
	#undef BLACK_LOG_DEBUG
#endif

#if( defined( BLACK_LOGS_CLOSE ) )
	#define BLACK_ISOLATE_LOGS_CLOSE
	#pragma push_macro( "BLACK_LOGS_CLOSE" )
	#undef BLACK_LOGS_CLOSE
#endif


#define BLACK_LOG_ASSERT( CHANNEL, FORMAT, ... )								\
{																				\
	const std::string message = Black::FormatString( FORMAT, ##__VA_ARGS__ );	\
	__android_log_write( ANDROID_LOG_ERROR, CHANNEL, message.c_str() );			\
}

#define BLACK_LOG_CRITICAL( CHANNEL, FORMAT, ... )								\
{																				\
	const std::string message = Black::FormatString( FORMAT, ##__VA_ARGS__ );	\
	__android_log_write( ANDROID_LOG_ERROR, CHANNEL, message.c_str() );			\
}

#define BLACK_LOG_ERROR( CHANNEL, FORMAT, ... )									\
{																				\
	const std::string message = Black::FormatString( FORMAT, ##__VA_ARGS__ );	\
	__android_log_write( ANDROID_LOG_ERROR, CHANNEL, message.c_str() );			\
}

#define BLACK_LOG_WARNING( CHANNEL, FORMAT, ... )								\
{																				\
	const std::string message = Black::FormatString( FORMAT, ##__VA_ARGS__ );	\
	__android_log_write( ANDROID_LOG_WARN, CHANNEL, message.c_str() );			\
}

#define BLACK_LOG_INFO( CHANNEL, FORMAT, ... )									\
{																				\
	const std::string message = Black::FormatString( FORMAT, ##__VA_ARGS__ );	\
	__android_log_write( ANDROID_LOG_INFO, CHANNEL, message.c_str() );			\
}

#define BLACK_LOG_VERBOSE( CHANNEL, FORMAT, ... )								\
{																				\
	const std::string message = Black::FormatString( FORMAT, ##__VA_ARGS__ );	\
	__android_log_write( ANDROID_LOG_VERBOSE, CHANNEL, message.c_str() );		\
}

#define BLACK_LOG_DEBUG( CHANNEL, FORMAT, ... )									\
{																				\
	const std::string message = Black::FormatString( FORMAT, ##__VA_ARGS__ );	\
	__android_log_write( ANDROID_LOG_DEBUG, CHANNEL, message.c_str() );			\
}

// Empty for Jni logging.
#define BLACK_LOGS_CLOSE( ... )
