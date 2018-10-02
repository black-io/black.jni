#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	template< typename... TArguments >
	JniObject JniObject::Construct( const JniClass& class_handle, const TArguments&... arguments )
	{
		constexpr size_t FRAME_SIZE = Black::JNI_LOCAL_FRAME_SIZE<TArguments...>;

		CRETD( !Black::JniConnection::IsValid(), {}, LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );

		const JniMemberFunction<void, TArguments...> constructor{ class_handle, "<init>" };
		CRETD( !constructor, {}, LOG_CHANNEL, "Failed to locate constructor with signature '{}'.", constructor.GetSignature().data() );

		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();

		if( FRAME_SIZE != 0 )
		{
			CRETD( local_env->PushLocalFrame( FRAME_SIZE ) != JNI_OK, {}, LOG_CHANNEL, "Failed to request local frame of {} items.", FRAME_SIZE );
		}

		JniObject result;
		result.AcquireObjectRef( local_env->NewObject( *class_handle, *constructor, Black::ToJni( arguments )... ) );
		result.m_class_handle = class_handle;

		if( local_env->ExceptionCheck() == JNI_TRUE )
		{
			BLACK_NON_RELEASE_CODE( local_env->ExceptionDescribe() );
			local_env->ExceptionClear();
			result.Invalidate();
		}

		CRET( FRAME_SIZE == 0, result );
		local_env->PopLocalFrame( nullptr );
		return result;
	}

	template< typename TOtherHandle >
	inline TOtherHandle JniObject::ConvertTo() const
	{
		static_assert( Black::IS_BASE_OF<JniObject, TOtherHandle>, "Output handle type should be derived from `Black::JniObject`." );

		CRET( !IsValid(), {} );

		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();

		JniClass current_class{ GetClass() };
		JniClass other_class{ JniClass::FromHandleType<TOtherHandle>() };
		CRET( !local_env->IsAssignableFrom( *current_class, *other_class ), {} );

		return { GetJniReference() };
	}

	inline JniObject& JniObject::operator=( const JniObject& other )
	{
		m_object_ref	= other.m_object_ref;
		m_class_handle	= other.m_class_handle;

		return *this;
	}

	inline const bool operator == ( const JniObject& left, const JniObject& right )
	{
		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		return local_env->IsSameObject( *left, *right );
	}

	inline const bool operator != ( const JniObject& left, const JniObject& right )
	{
		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		return !local_env->IsSameObject( *left, *right );
	}
}
}
}
