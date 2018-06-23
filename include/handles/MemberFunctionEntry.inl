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
		constexpr size_t FRAME_SIZE = Black::JNI_LOCAL_FRAME_SIZE<TResult, TArguments...>;

		CRETD( m_local_env == nullptr, {}, LOG_CHANNEL, "{}:{} - Attempt to call JNI function using invalid JNI environment.", __func__, __LINE__ );

		if( FRAME_SIZE != 0 )
		{
			CRETD( m_local_env->PushLocalFrame( FRAME_SIZE ) != JNI_OK, {}, LOG_CHANNEL, "Failed to request local frame of {} items.", FRAME_SIZE );
		}

		auto jni_result = (JniResult)(m_local_env->*FUNCTION_HANDLER)( m_object_ref, m_function_id, Black::ToJni( arguments )... );

		TResult result;
		Black::FromJni( jni_result, result );
		CRET( FRAME_SIZE == 0, result );

		m_local_env->PopLocalFrame( nullptr );
		return result;
	}

	template< typename TResult, typename... TArguments >
	inline TResult MemberFunctionEntry<TResult, TArguments...>::CallNonVirtual( jclass class_ref, const TArguments&... arguments ) const
	{
		constexpr size_t FRAME_SIZE = Black::JNI_LOCAL_FRAME_SIZE<TResult, TArguments...>;

		EXPECTS( class_ref != nullptr );
		CRETD( m_local_env == nullptr, {}, LOG_CHANNEL, "{}:{} - Attempt to call JNI function using invalid JNI environment.", __func__, __LINE__ );

		if( FRAME_SIZE != 0 )
		{
			CRETD( m_local_env->PushLocalFrame( FRAME_SIZE ) != JNI_OK, {}, LOG_CHANNEL, "Failed to request local frame of {} items.", FRAME_SIZE );
		}

		auto jni_result = (JniResult)(m_local_env->*NONVIRTUAL_FUNCTION_HANDLER)( m_object_ref, class_ref, m_function_id, Black::ToJni( arguments )... );

		TResult result;
		Black::FromJni( jni_result, result );
		CRET( FRAME_SIZE == 0, result );

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
		constexpr size_t FRAME_SIZE = Black::JNI_LOCAL_FRAME_SIZE<TArguments...>;

		CRETD( m_local_env == nullptr, , LOG_CHANNEL, "{}:{} - Attempt to call JNI function using invalid JNI environment.", __func__, __LINE__ );

		if( FRAME_SIZE != 0 )
		{
			CRETD( m_local_env->PushLocalFrame( FRAME_SIZE ) != JNI_OK, , LOG_CHANNEL, "Failed to request local frame of {} items.", FRAME_SIZE );
		}

		(m_local_env->*FUNCTION_HANDLER)( m_object_ref, m_function_id, Black::ToJni( arguments )... );

		CRET( FRAME_SIZE == 0 );
		m_local_env->PopLocalFrame( nullptr );
	}

	template< typename... TArguments >
	inline void MemberFunctionEntry<void, TArguments...>::CallNonVirtual( jclass class_ref, const TArguments&... arguments ) const
	{
		constexpr size_t FRAME_SIZE = Black::JNI_LOCAL_FRAME_SIZE<TArguments...>;

		EXPECTS( class_ref != nullptr );
		CRETD( m_local_env == nullptr, , LOG_CHANNEL, "{}:{} - Attempt to call JNI function using invalid JNI environment.", __func__, __LINE__ );

		if( FRAME_SIZE != 0 )
		{
			CRETD( m_local_env->PushLocalFrame( FRAME_SIZE ) != JNI_OK, , LOG_CHANNEL, "Failed to request local frame of {} items.", FRAME_SIZE );
		}

		(m_local_env->*NONVIRTUAL_FUNCTION_HANDLER)( m_object_ref, class_ref, m_function_id, Black::ToJni( arguments )... );

		CRET( FRAME_SIZE == 0 );
		m_local_env->PopLocalFrame( nullptr );
	}
}
}
}
}
