#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	template< typename TResult, typename... TArguments >
	JniStaticFunction<TResult, TArguments...>::JniStaticFunction( std::string_view class_name, std::string_view function_name )
		: JniStaticFunction{ Black::JniClass{ class_name }, function_name, Black::IGNORE_FALURE }
	{
		ENSURES( IsValid() );
	}

	template< typename TResult, typename... TArguments >
	JniStaticFunction<TResult, TArguments...>::JniStaticFunction( const Black::JniClass& class_handle, std::string_view function_name )
		: JniStaticFunction{ class_handle, function_name, Black::IGNORE_FALURE }
	{
		ENSURES( IsValid() );
	}

	template< typename TResult, typename... TArguments >
	JniStaticFunction<TResult, TArguments...>::JniStaticFunction( std::string_view class_name, std::string_view function_name, Black::IgnoreFailure )
		: JniStaticFunction{ Black::JniClass{ class_name }, function_name, Black::IGNORE_FALURE }
	{

	}

	template< typename TResult, typename... TArguments >
	JniStaticFunction<TResult, TArguments...>::JniStaticFunction( const Black::JniClass& class_handle, std::string_view function_name, Black::IgnoreFailure )
		: m_class_handle{ class_handle }
	{
		CRETD( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );
		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();

		char* function_name_buffer = static_cast<char*>( alloca( function_name.length() ) );
		Black::CopyMemory( function_name_buffer, function_name.data(), function_name.length() );
		function_name_buffer[ function_name.length() ] = 0;

		ENSURES( m_class_handle );
		m_function_id = local_env->GetStaticMethodID( *m_class_handle, function_name_buffer, Signature::GetData() );

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
