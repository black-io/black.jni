#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
inline namespace Functions
{
	template< typename TResult, typename... TArguments >
	JniMemberFunction<TResult (TArguments...)>::JniMemberFunction( std::string_view class_name, std::string_view function_name )
		: JniMemberFunction{ Black::JniClass{ class_name }, function_name, Black::IGNORE_FALURE }
	{
		ENSURES( IsValid() );
	}

	template< typename TResult, typename... TArguments >
	JniMemberFunction<TResult (TArguments...)>::JniMemberFunction( const Black::JniClass& class_handle, std::string_view function_name )
		: JniMemberFunction{ class_handle, function_name, Black::IGNORE_FALURE }
	{
		ENSURES( IsValid() );
	}

	template< typename TResult, typename... TArguments >
	JniMemberFunction<TResult (TArguments...)>::JniMemberFunction( std::string_view class_name, std::string_view function_name, Black::IgnoreFailure )
		: JniMemberFunction{ Black::JniClass{ class_name }, function_name, Black::IGNORE_FALURE }
	{

	}

	template< typename TResult, typename... TArguments >
	JniMemberFunction<TResult (TArguments...)>::JniMemberFunction( const Black::JniClass& class_handle, std::string_view function_name, Black::IgnoreFailure )
		: m_class_handle{ class_handle }
	{
		CRETD( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );
		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();

		char* function_name_buffer = static_cast<char*>( alloca( function_name.length() ) );
		Black::CopyMemory( function_name_buffer, function_name.data(), function_name.length() );
		function_name_buffer[ function_name.length() ] = 0;

		ENSURES( m_class_handle );
		m_function_id = local_env->GetMethodID( *m_class_handle, function_name_buffer, Signature::GetData() );

		CRET( local_env->ExceptionCheck() != JNI_TRUE );

		BLACK_NON_RELEASE_CODE( local_env->ExceptionDescribe() );
		local_env->ExceptionClear();
		m_function_id = nullptr;
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniMemberFunction<TResult (TArguments...)>::Call( const Black::JniObject& object_handle, const TArguments&... arguments ) const
	{
		return Call( Black::JniConnection::GetLocalEnvironment(), *object_handle, arguments... );
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniMemberFunction<TResult (TArguments...)>::Call( Black::NotNull<jobject> object_ref, const TArguments&... arguments ) const
	{
		return Call( Black::JniConnection::GetLocalEnvironment(), object_ref, arguments... );
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniMemberFunction<TResult (TArguments...)>::CallNonVirtual( const Black::JniObject& object_handle, const TArguments&... arguments ) const
	{
		return CallNonVirtual( Black::JniConnection::GetLocalEnvironment(), *object_handle, arguments... );
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniMemberFunction<TResult (TArguments...)>::CallNonVirtual( Black::NotNull<jobject> object_ref, const TArguments&... arguments ) const
	{
		return CallNonVirtual( Black::JniConnection::GetLocalEnvironment(), object_ref, arguments... );
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniMemberFunction<TResult (TArguments...)>::Call( JNIEnv* local_env, jobject object_ref, const TArguments&... arguments ) const
	{
		return EntryPoint{ local_env, object_ref, m_function_id }.Call( arguments... );
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniMemberFunction<TResult (TArguments...)>::CallNonVirtual( JNIEnv* local_env, jobject object_ref, const TArguments&... arguments ) const
	{
		return EntryPoint{ local_env, object_ref, m_function_id }.CallNonVirtual( *m_class_handle, arguments... );
	}
}
}
}
}
