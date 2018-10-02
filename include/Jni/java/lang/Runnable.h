#pragma once


namespace Jni
{
inline namespace java
{
inline namespace lang
{
	// Handle for `java.lang.Runnable` objects.
	class Runnable final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'R', 'u', 'n', 'n', 'a', 'b', 'l', 'e'>;

	// Construction and assignation.
	public:
		Runnable() = default;
		Runnable( jobject object_ref ) : Black::JniObject{ object_ref } {};
		Runnable( const Runnable& other ) : Black::JniObject( other ) {};
		Runnable( Runnable&& other ) : Black::JniObject( std::move( other ) ) {};


		const Runnable& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const Runnable& operator = ( const Runnable& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Runnable& operator = ( Runnable&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };
	};
}
}
}


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Internal
{
	// JNI context specification for handles to `java.lang.Runnable` class.
	template<>
	struct NativeContext<::Jni::java::lang::Runnable> : public Black::NativeObjectContext<::Jni::java::lang::Runnable>
	{

	};
}
}
}
}
