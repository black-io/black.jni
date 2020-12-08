#pragma once


// Define the owned logging macros.

#if( BLACK_RELEASE_BUILD )
	#define BLACK_JNI_FORMAT_MESSAGE( FORMAT, ... ) const std::string message{ Black::FormatString( FORMAT, ##__VA_ARGS__ ) };
#else
	#define BLACK_JNI_FORMAT_MESSAGE( FORMAT, ... )																			\
	const std::string message{ Black::FormatString(																			\
		FORMAT " [at `{}` from " __FILE__ ":" BLACK_STRINGIFICATION( __LINE__ ) "]",										\
		##__VA_ARGS__, __FUNCTION__																							\
	) }
#endif


#define BLACK_LOG_ASSERT( CHANNEL, FORMAT, ... )								\
{																				\
	BLACK_JNI_FORMAT_MESSAGE( FORMAT, ##__VA_ARGS__ );							\
	__android_log_write( ANDROID_LOG_FATAL, CHANNEL, message.c_str() );			\
}

#define BLACK_LOG_CRITICAL( CHANNEL, FORMAT, ... )								\
{																				\
	BLACK_JNI_FORMAT_MESSAGE( FORMAT, ##__VA_ARGS__ );							\
	__android_log_write( ANDROID_LOG_FATAL, CHANNEL, message.c_str() );			\
}

#define BLACK_LOG_ERROR( CHANNEL, FORMAT, ... )									\
{																				\
	BLACK_JNI_FORMAT_MESSAGE( FORMAT, ##__VA_ARGS__ );							\
	__android_log_write( ANDROID_LOG_ERROR, CHANNEL, message.c_str() );			\
}

#define BLACK_LOG_WARNING( CHANNEL, FORMAT, ... )								\
{																				\
	BLACK_JNI_FORMAT_MESSAGE( FORMAT, ##__VA_ARGS__ );							\
	__android_log_write( ANDROID_LOG_WARN, CHANNEL, message.c_str() );			\
}

#define BLACK_LOG_INFO( CHANNEL, FORMAT, ... )									\
{																				\
	BLACK_JNI_FORMAT_MESSAGE( FORMAT, ##__VA_ARGS__ );							\
	__android_log_write( ANDROID_LOG_INFO, CHANNEL, message.c_str() );			\
}

#define BLACK_LOG_VERBOSE( CHANNEL, FORMAT, ... )								\
{																				\
	BLACK_JNI_FORMAT_MESSAGE( FORMAT, ##__VA_ARGS__ );							\
	__android_log_write( ANDROID_LOG_VERBOSE, CHANNEL, message.c_str() );		\
}

#define BLACK_LOG_DEBUG( CHANNEL, FORMAT, ... )									\
{																				\
	BLACK_JNI_FORMAT_MESSAGE( FORMAT, ##__VA_ARGS__ );							\
	__android_log_write( ANDROID_LOG_DEBUG, CHANNEL, message.c_str() );			\
}

#define BLACK_LOGS_CLOSE( ... )
