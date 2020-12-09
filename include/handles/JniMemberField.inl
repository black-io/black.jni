#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	template< typename TNativeType >
	JniMemberField<TNativeType>::JniMemberField( std::string_view class_name, std::string_view field_name )
		: JniMemberField{ Black::JniClass{ class_name }, field_name, Black::IGNORE_FALURE }
	{
		ENSURES( IsValid() );
	}

	template< typename TNativeType >
	JniMemberField<TNativeType>::JniMemberField( const Black::JniClass& class_handle, std::string_view field_name )
		: JniMemberField{ class_handle, field_name, Black::IGNORE_FALURE }
	{
		ENSURES( IsValid() );
	}

	template< typename TNativeType >
	JniMemberField<TNativeType>::JniMemberField( std::string_view class_name, std::string_view field_name, Black::IgnoreFailure )
		: JniMemberField{ Black::JniClass{ class_name }, field_name, Black::IGNORE_FALURE }
	{

	}

	template< typename TNativeType >
	JniMemberField<TNativeType>::JniMemberField( const Black::JniClass& class_handle, std::string_view field_name, Black::IgnoreFailure )
	{
		CRETD( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );
		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();

		ENSURES( class_handle );
		m_field_id = local_env->GetFieldID( *class_handle, field_name.data(), Signature::GetData() );

		CRET( local_env->ExceptionCheck() != JNI_TRUE );

		BLACK_NON_RELEASE_CODE( local_env->ExceptionDescribe() );
		local_env->ExceptionClear();
		m_field_id = nullptr;
	}

	template< typename TNativeType >
	inline const bool JniMemberField<TNativeType>::GetValue( const JniObject& object_handle, TNativeType& value_storage ) const
	{
		return GetValue( Black::JniConnection::GetLocalEnvironment(), *object_handle, value_storage );
	}

	template< typename TNativeType >
	inline const bool JniMemberField<TNativeType>::GetValue( jobject object_ref, TNativeType& value_storage ) const
	{
		return GetValue( Black::JniConnection::GetLocalEnvironment(), object_ref, value_storage );
	}

	template< typename TNativeType >
	inline TNativeType JniMemberField<TNativeType>::GetValue( const JniObject& object_handle, const TNativeType& default_value ) const
	{
		TNativeType native_result;
		CRETD( !GetValue( object_handle, native_result ), default_value, LOG_CHANNEL, "Failed to read value of field." );
		return native_result;
	}

	template< typename TNativeType >
	inline TNativeType JniMemberField<TNativeType>::GetValue( jobject object_ref, const TNativeType& default_value ) const
	{
		TNativeType native_result;
		CRETD( !GetValue( object_ref, native_result ), default_value, LOG_CHANNEL, "Failed to read value of field." );
		return native_result;
	}

	template< typename TNativeType >
	inline const bool JniMemberField<TNativeType>::SetValue( const JniObject& object_handle, const TNativeType& value_storage ) const
	{
		return SetValue( Black::JniConnection::GetLocalEnvironment(), *object_handle, value_storage );
	}

	template< typename TNativeType >
	inline const bool JniMemberField<TNativeType>::SetValue( jobject object_ref, const TNativeType& value_storage ) const
	{
		return SetValue( Black::JniConnection::GetLocalEnvironment(), object_ref, value_storage );
	}

	template< typename TNativeType >
	inline const bool JniMemberField<TNativeType>::GetValue( JNIEnv* local_env, jobject object_ref, TNativeType& value_storage ) const
	{
		CRETD( local_env == nullptr, false, LOG_CHANNEL, "Attempt to use member field with invalid JNI connection." );
		CRETD( m_field_id == nullptr, false, LOG_CHANNEL, "Invalid member field - field not found for specified class." );

		if( LOCAL_FRAME_SIZE != 0 )
		{
			const size_t frame_size = LOCAL_FRAME_SIZE;
			CRETD( local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK, false, LOG_CHANNEL, "Failed to request local frame of {} items.", frame_size );
		}

		auto jni_value = (JniType)(local_env->*FIELD_READ_HANDLER)( object_ref, m_field_id );
		Black::FromJni( jni_value, value_storage );

		CRET( LOCAL_FRAME_SIZE == 0, true );
		local_env->PopLocalFrame( nullptr );
		return true;
	}

	template< typename TNativeType >
	inline const bool JniMemberField<TNativeType>::SetValue( JNIEnv* local_env, jobject object_ref, const TNativeType& value_storage ) const
	{
		CRETD( local_env == nullptr, false, LOG_CHANNEL, "Attempt to use member field with invalid JNI connection." );
		CRETD( m_field_id == nullptr, false, LOG_CHANNEL, "Invalid member field - field not found for specified class." );

		if( LOCAL_FRAME_SIZE != 0 )
		{
			const size_t frame_size = LOCAL_FRAME_SIZE;
			CRETD( local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK, false, LOG_CHANNEL, "Failed to request local frame of {} items.", frame_size );
		}

		JniType jni_value;
		Black::ToJni( value_storage, jni_value );
		(local_env->*FIELD_WRITE_HANDLER)( object_ref, m_field_id, jni_value );

		CRET( LOCAL_FRAME_SIZE == 0, true );
		local_env->PopLocalFrame( nullptr );
		return true;
	}
}
}
}
