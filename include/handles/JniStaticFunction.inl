#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	template< typename TResult, typename... TArguments >
	JniStaticFunction<TResult, TArguments...>::JniStaticFunction( Black::StringView class_name, Black::StringView function_name )
		: JniStaticFunction{ Black::JniClass{ class_name }, function_name, Black::IGNORE_FALURES }
	{
		ENSURES( IsValid() );
	}

	template< typename TResult, typename... TArguments >
	JniStaticFunction<TResult, TArguments...>::JniStaticFunction( const Black::JniClass& class_handle, Black::StringView function_name )
		: JniStaticFunction{ class_handle, function_name, Black::IGNORE_FALURES }
	{
		ENSURES( IsValid() );
	}

	template< typename TResult, typename... TArguments >
	JniStaticFunction<TResult, TArguments...>::JniStaticFunction( Black::StringView class_name, Black::StringView function_name, Black::IgnoreFailure )
		: JniStaticFunction{ Black::JniClass{ class_name }, function_name, Black::IGNORE_FALURES }
	{

	}

	template< typename TResult, typename... TArguments >
	JniStaticFunction<TResult, TArguments...>::JniStaticFunction( const Black::JniClass& class_handle, Black::StringView function_name, Black::IgnoreFailure )
		: m_class_handle{ class_handle }
	{
		CRETD( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );
		JNIEnv* local_env = Black::JniConnection().GetLocalEnvironment();

		ENSURES( m_class_handle );
		m_function_id = local_env->GetStaticMethodID( *m_class_handle, function_name.data(), Signature::GetData() );

		CRET( local_env->ExceptionCheck() != JNI_TRUE );

		BLACK_NON_RELEASE_CODE( local_env->ExceptionDescribe() );
		local_env->ExceptionClear();
		m_function_id = nullptr;
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniStaticFunction<TResult, TArguments...>::Call( const TArguments&... arguments ) const
	{
		return Call( Black::JniConnection::GetLocalEnvironment(), arguments... );
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniStaticFunction<TResult, TArguments...>::Call( JNIEnv* local_env, const TArguments&... arguments ) const
	{
		return EntryPoint{ local_env, *m_class_handle, m_function_id }.Call( arguments... );
	}
}
}
}
