#include <black.jni.h>


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	JniClass::JniClass( Black::StringView class_name )
	{
		AcquireClassReference( class_name );
	}

	JniClass& JniClass::operator=( jclass class_ref )
	{
		auto new_ref = Black::JniConnection::GetClassStorage().GetClassReference( class_ref );
		std::swap( m_class_ref, new_ref );

		return *this;
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

	void JniClass::AcquireClassReference( Black::StringView class_name )
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
}
}
}
