#include <jni.private.h>


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	JniClass::JniClass( std::string_view class_name )
	{
		AcquireClassReference( class_name );
	}

	JniClass::JniClass( jclass class_ref )
		: m_class_ref{ Black::JniConnection::GetClassStorage().GetClassReference( class_ref ) }
	{

	}

	void JniClass::Invalidate()
	{
		m_class_ref.reset();
	}

	const std::string JniClass::GetCanonicalName() const
	{
		CRET( !IsValid(), {} );
		return Black::JniConnection::GetCanonicalClassName( *this );
	}

	const std::string JniClass::GetName() const
	{
		CRET( !IsValid(), {} );
		return Black::JniConnection::GetClassName( *this );
	}

	const std::string JniClass::GetSimpleName() const
	{
		CRET( !IsValid(), {} );
		return Black::JniConnection::GetSimpleClassName( *this );
	}

	JniClass JniClass::GetParentClass() const
	{
		CRET( !IsValid(), {} );
		return Black::JniConnection::GetParentClass( *this );
	}

	void JniClass::AcquireClassReference( std::string_view class_name )
	{
		Invalidate();
		EXPECTS( !class_name.empty() );

		m_class_ref = Black::JniConnection::GetClassStorage().GetClassReference( class_name );
		ENSURES( IsValid() );
	}

	void JniClass::AcquireClassReference( jobject object_ref )
	{
		Invalidate();
		CRET( object_ref == nullptr );

		m_class_ref = Black::JniConnection::GetClassStorage().GetClassReference( object_ref );
		ENSURES( IsValid() );
	}

	const bool operator == ( const JniClass& left, const JniClass& right )
	{
		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		return local_env->IsSameObject( *left, *right );
	}

	const bool operator != ( const JniClass& left, const JniClass& right )
	{
		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		return !local_env->IsSameObject( *left, *right );
	}
}
}
}
