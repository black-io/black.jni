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
	inline MemberFunctionEntry<TResult, TArguments...>::MemberFunctionEntry( JNIEnv* local_env, jobject object_ref, jmethodID function_id )
		: m_local_env{ local_env }
		, m_object_ref{ object_ref }
		, m_function_id{ function_id }
	{
		ENSURES( m_object_ref != nullptr );
		ENSURES( m_function_id != nullptr );
	}

	template< typename TResult, typename... TArguments >
	inline TResult MemberFunctionEntry<TResult, TArguments...>::Call( const TArguments&... arguments ) const
	{
		TResult result{};

		CRETD( m_local_env == nullptr, result, LOG_CHANNEL, "{}:{} - Attempt to call JNI function using invalid JNI environment.", __func__, __LINE__ );

		constexpr size_t frame_size = Black::CalculateLocalFrameSize<TResult, TArguments...>();
		if( frame_size != 0 )
		{
			CRETD( m_local_env->PushLocalFrame( frame_size ) != JNI_OK, result, LOG_CHANNEL, "Failed to request local frame of {} items.", frame_size );
		}

		auto jni_result = (JniResult)(m_local_env->*FUNCTION_HANDLER)( m_object_ref, m_function_id, Black::ToJni( arguments )... );

		Black::FromJni( jni_result, result );
		CRET( frame_size == 0, result );

		m_local_env->PopLocalFrame( nullptr );
		return result;
	}

	template< typename TResult, typename... TArguments >
	inline TResult MemberFunctionEntry<TResult, TArguments...>::CallNonVirtual( jclass class_ref, const TArguments&... arguments ) const
	{
		TResult result{};

		EXPECTS( class_ref != nullptr );
		CRETD( m_local_env == nullptr, result, LOG_CHANNEL, "{}:{} - Attempt to call JNI function using invalid JNI environment.", __func__, __LINE__ );

		constexpr size_t frame_size = Black::CalculateLocalFrameSize<TResult, TArguments...>();
		if( frame_size != 0 )
		{
			CRETD( m_local_env->PushLocalFrame( frame_size ) != JNI_OK, result, LOG_CHANNEL, "Failed to request local frame of {} items.", frame_size );
		}

		auto jni_result = (JniResult)(m_local_env->*NONVIRTUAL_FUNCTION_HANDLER)( m_object_ref, class_ref, m_function_id, Black::ToJni( arguments )... );

		Black::FromJni( jni_result, result );
		CRET( frame_size == 0, result );

		m_local_env->PopLocalFrame( nullptr );
		return result;
	}


	template< typename... TArguments >
	inline MemberFunctionEntry<void, TArguments...>::MemberFunctionEntry( JNIEnv* local_env, jobject object_ref, jmethodID function_id )
		: m_local_env{ local_env }
		, m_object_ref{ object_ref }
		, m_function_id{ function_id }
	{
		ENSURES( m_object_ref != nullptr );
		ENSURES( m_function_id != nullptr );
	}

	template< typename... TArguments >
	inline void MemberFunctionEntry<void, TArguments...>::Call( const TArguments&... arguments ) const
	{
		CRETD( m_local_env == nullptr, , LOG_CHANNEL, "{}:{} - Attempt to call JNI function using invalid JNI environment.", __func__, __LINE__ );

		constexpr size_t frame_size = Black::CalculateLocalFrameSize<TArguments...>();
		if( frame_size != 0 )
		{
			CRETD( m_local_env->PushLocalFrame( frame_size ) != JNI_OK, , LOG_CHANNEL, "Failed to request local frame of {} items.", frame_size );
		}

		(m_local_env->*FUNCTION_HANDLER)( m_object_ref, m_function_id, Black::ToJni( arguments )... );

		CRET( frame_size == 0 );
		m_local_env->PopLocalFrame( nullptr );
	}

	template< typename... TArguments >
	inline void MemberFunctionEntry<void, TArguments...>::CallNonVirtual( jclass class_ref, const TArguments&... arguments ) const
	{
		EXPECTS( class_ref != nullptr );
		CRETD( m_local_env == nullptr, , LOG_CHANNEL, "{}:{} - Attempt to call JNI function using invalid JNI environment.", __func__, __LINE__ );

		constexpr size_t frame_size = Black::CalculateLocalFrameSize<TArguments...>();
		if( frame_size != 0 )
		{
			CRETD( m_local_env->PushLocalFrame( frame_size ) != JNI_OK, , LOG_CHANNEL, "Failed to request local frame of {} items.", frame_size );
		}

		(m_local_env->*NONVIRTUAL_FUNCTION_HANDLER)( m_object_ref, class_ref, m_function_id, Black::ToJni( arguments )... );

		CRET( frame_size == 0 );
		m_local_env->PopLocalFrame( nullptr );
	}
}
}
}
}
