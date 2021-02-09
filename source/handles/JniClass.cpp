#include <black/jni/handles.h>


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
inline namespace Objects
{
	JniClass::JniClass( std::string_view class_name )
	{
		AcquireClassReference( class_name );
	}

	JniClass::JniClass( jclass class_ref )
		: m_class_ref{ Internal::ClassRegistry::GetClassReference( class_ref ) }
	{
	}

	void JniClass::Invalidate()
	{
		m_class_ref.reset();
	}

	const std::string JniClass::GetCanonicalName() const
	{
		CRET( !IsValid(), {} );
		return Internal::ClassRegistry::GetCanonicalClassName( GetJniReference() );
	}

	const std::string JniClass::GetName() const
	{
		CRET( !IsValid(), {} );
		return Internal::ClassRegistry::GetClassName( GetJniReference() );
	}

	const std::string JniClass::GetSimpleName() const
	{
		CRET( !IsValid(), {} );
		return Internal::ClassRegistry::GetSimpleClassName( GetJniReference() );
	}

	JniClass JniClass::GetParentClass() const
	{
		CRET( !IsValid(), {} );
		return Internal::ClassRegistry::GetParentClass( GetJniReference() );
	}

	void JniClass::AcquireClassReference( std::string_view class_name )
	{
		Invalidate();
		EXPECTS( !class_name.empty() );

		m_class_ref = Internal::ClassRegistry::GetClassReference( class_name );
		ENSURES( IsValid() );
	}

	void JniClass::AcquireClassReference( jobject object_ref )
	{
		Invalidate();
		CRET( object_ref == nullptr );

		m_class_ref = Internal::ClassRegistry::GetClassReference( object_ref );
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
}
