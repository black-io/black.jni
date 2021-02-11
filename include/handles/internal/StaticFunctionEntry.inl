#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
	template< typename TResult, typename... TArguments >
	inline StaticFunctionEntry<TResult, TArguments...>::StaticFunctionEntry( JNIEnv* local_env, jclass class_ref, jmethodID function_id )
		: m_local_env{ local_env }
		, m_class_ref{ class_ref }
		, m_function_id{ function_id }
	{
		ENSURES( m_class_ref != nullptr );
		ENSURES( m_function_id != nullptr );
	}

	template< typename TResult, typename... TArguments >
	inline TResult StaticFunctionEntry<TResult, TArguments...>::Call( const TArguments&... arguments ) const
	{
		TResult result{};

		CRETD( m_local_env == nullptr, result, LOG_CHANNEL, "{}:{} - Attempt to call JNI function using invalid JNI environment.", __func__, __LINE__ );

		constexpr size_t frame_size = Black::CalculateLocalFrameSize<TResult, TArguments...>();
		if( frame_size != 0 )
		{
			CRETD( m_local_env->PushLocalFrame( frame_size ) != JNI_OK, result, LOG_CHANNEL, "Failed to request local frame of {} items.", frame_size );
		}

		auto jni_result = (JniResult)(m_local_env->*FUNCTION_HANDLER)( m_class_ref, m_function_id, Black::ConvertToJni( arguments )... );

		Black::ConvertFromJni( jni_result, result );
		CRET( frame_size == 0, result );

		m_local_env->PopLocalFrame( nullptr );
		return result;
	}


	template< typename... TArguments >
	inline StaticFunctionEntry<void, TArguments...>::StaticFunctionEntry( JNIEnv* local_env, jclass class_ref, jmethodID function_id )
		: m_local_env{ local_env }
		, m_class_ref{ class_ref }
		, m_function_id{ function_id }
	{
		ENSURES( m_local_env != nullptr );
		ENSURES( m_function_id != 0 );
	}

	template< typename... TArguments >
	inline void StaticFunctionEntry<void, TArguments...>::Call( const TArguments&... arguments ) const
	{
		CRETD( m_local_env == nullptr, , LOG_CHANNEL, "{}:{} - Attempt to call JNI function using invalid JNI environment.", __func__, __LINE__ );

		constexpr size_t frame_size = Black::CalculateLocalFrameSize<TArguments...>();
		if( frame_size != 0 )
		{
			CRETD( m_local_env->PushLocalFrame( frame_size ) != JNI_OK, , LOG_CHANNEL, "Failed to request local frame of {} items.", frame_size );
		}

		(m_local_env->*FUNCTION_HANDLER)( m_class_ref, m_function_id, Black::ConvertToJni( arguments )... );

		CRET( frame_size == 0 );
		m_local_env->PopLocalFrame( nullptr );
	}
}
}
}
}
