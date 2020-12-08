#pragma once


// Store the current logging directives into macro stack.

#pragma push_macro( "BLACK_LOG_ASSERT" )
#undef BLACK_LOG_ASSERT

#pragma push_macro( "BLACK_LOG_CRITICAL" )
#undef BLACK_LOG_CRITICAL

#pragma push_macro( "BLACK_LOG_ERROR" )
#undef BLACK_LOG_ERROR

#pragma push_macro( "BLACK_LOG_WARNING" )
#undef BLACK_LOG_WARNING

#pragma push_macro( "BLACK_LOG_INFO" )
#undef BLACK_LOG_INFO

#pragma push_macro( "BLACK_LOG_VERBOSE" )
#undef BLACK_LOG_VERBOSE

#pragma push_macro( "BLACK_LOGS_CLOSE" )
#undef BLACK_LOGS_CLOSE
