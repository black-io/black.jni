#include <black/jni/handles.h>


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
inline namespace Objects
{
	JniObject::JniObject( const JniObject& other )
		: m_object_ref{ other.m_object_ref }
		, m_class_handle{ other.m_class_handle }
	{

	}

	JniObject::JniObject( JniObject&& other )
		: m_object_ref{ std::move( other.m_object_ref ) }
		, m_class_handle{ std::move( other.m_class_handle ) }
	{

	}

	JniObject::JniObject( const JniClass& class_handle )
		: m_object_ref( class_handle.m_class_ref )
	{

	}

	JniObject::JniObject( JniClass&& class_handle )
		: m_object_ref( std::move( class_handle.m_class_ref ) )
	{

	}

	JniObject::JniObject( jobject object_ref )
	{
		AcquireObjectRef( object_ref );
	}

	void JniObject::Invalidate()
	{
		m_class_handle.Invalidate();
		m_object_ref.reset();
	}

	void JniObject::Lock() const
	{
		EXPECTS_DEBUG( IsValid() );
		CRETE( !IsValid(), , LOG_CHANNEL, "Failed to lock the null object." );
		CRETE( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "Attempt to use invalid JNI connection." );

		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		const int32_t access_result = local_env->MonitorEnter( GetJniReference() );
		EXPECTS( access_result == 0 );
	}

	void JniObject::Unlock() const
	{
		EXPECTS_DEBUG( IsValid() );
		CRETE( !IsValid(), , LOG_CHANNEL, "Failed to lock the null object." );
		CRETE( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "Attempt to use invalid JNI connection." );

		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		const int32_t access_result = local_env->MonitorExit( GetJniReference() );
		EXPECTS( access_result == 0 );

		if( local_env->ExceptionCheck() == JNI_TRUE )
		{
			BLACK_NON_RELEASE_CODE( local_env->ExceptionDescribe() );
			local_env->ExceptionClear();
			local_env->FatalError( "Failed to release the synchronization from non-owning thread." );
		}
	}

	void JniObject::Notify() const
	{
		EXPECTS_DEBUG( IsValid() );
		CRETE( !IsValid(), , LOG_CHANNEL, "Failed to notify from the null object." );

		Black::JniConnection::NotifyFromObject( GetJniReference() );
	}

	void JniObject::NotifyAll() const
	{
		EXPECTS_DEBUG( IsValid() );
		CRETE( !IsValid(), , LOG_CHANNEL, "Failed to notify from the null object." );

		Black::JniConnection::NotifyAllFromObject( GetJniReference() );
	}

	void JniObject::Wait() const
	{
		EXPECTS_DEBUG( IsValid() );
		CRETE( !IsValid(), , LOG_CHANNEL, "Failed to wait from the null object." );

		Black::JniConnection::WaitFromObject( GetJniReference() );
	}

	void JniObject::Wait( const std::chrono::milliseconds millis ) const
	{
		EXPECTS_DEBUG( IsValid() );
		CRETE( !IsValid(), , LOG_CHANNEL, "Failed to wait from the null object." );

		Black::JniConnection::WaitFromObject( GetJniReference(), millis.count() );
	}

	void JniObject::Wait( const std::chrono::milliseconds millis, std::chrono::nanoseconds nanos ) const
	{
		EXPECTS_DEBUG( IsValid() );
		CRETE( !IsValid(), , LOG_CHANNEL, "Failed to wait from the null object." );

		Black::JniConnection::WaitFromObject( GetJniReference(), millis.count(), nanos.count() );
	}

	const bool JniObject::IsInstanceOf( const JniClass& base_class ) const
	{
		CRET( !( IsValid() && base_class ), false );

		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		return local_env->IsInstanceOf( GetJniReference(), *base_class );
	}

	void JniObject::DeleteObjectRef( jobject object_ref )
	{
		CRET( object_ref == nullptr );
		CRETE( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "Attempt to use invalid JNI connection." );

		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		local_env->DeleteGlobalRef( object_ref );
	}

	void JniObject::EnsureClassHandle() const
	{
		CRET( m_class_handle );
		CRET( !IsValid() );

		m_class_handle.AcquireClassReference( GetJniReference() );
	}

	void JniObject::AcquireObjectRef( jobject object_ref )
	{
		CRETE( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "Attempt to use invalid JNI connection." );

		Invalidate();
		CRET( object_ref == nullptr );

		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		m_object_ref		= { local_env->NewGlobalRef( object_ref ), JniObject::DeleteObjectRef };
	}
}
}
}
}
