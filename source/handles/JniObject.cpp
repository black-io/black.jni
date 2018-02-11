#include <black.jni.h>


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
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

	const bool JniObject::IsInstanceOf( const JniClass& base_class ) const
	{
		CRET( !( IsValid() && base_class ), false );

		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		return local_env->IsInstanceOf( GetJniReference(), *base_class );
	}

	void JniObject::DeleteObjectRef( jobject object_ref )
	{
		CRET( object_ref == nullptr );
		CRETM( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );

		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		local_env->DeleteGlobalRef( object_ref );
	}

	void JniObject::EnsureClassHandle() const
	{
		CRET( !IsValid() );
		CRET( m_class_handle );

		m_class_handle.AcquireClassReference( GetJniReference() );
	}

	void JniObject::AcquireObjectRef( jobject object_ref )
	{
		CRETM( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );

		Invalidate();
		CRET( object_ref == nullptr );

		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		m_object_ref		= { local_env->NewGlobalRef( object_ref ), JniObject::DeleteObjectRef };
	}
}
}
}
