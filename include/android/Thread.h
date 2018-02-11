#pragma once


namespace Android
{
inline namespace Java
{
inline namespace Lang
{
	// Handle for `java.lang.Thread` objects.
	class Thread : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'T', 'h', 'r', 'e', 'a', 'd'>;

	// Construction and assignation.
	public:
		Thread() = default;
		Thread( jobject object_ref ) : Black::JniObject{ object_ref } {};
		Thread( const Thread& other ) : Black::JniObject( other ) {};
		Thread( Thread&& other ) : Black::JniObject( std::move( other ) ) {};


		const Thread& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const Thread& operator = ( const Thread& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Thread& operator = ( Thread&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };
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
namespace Traits
{
	// JNI context specification for handles to `java.lang.Thread` class.
	template<>
	struct NativeContext<::Android::Java::Lang::Thread> : public Black::NativeObjectContext<::Android::Java::Lang::Thread>
	{

	};
}
}
}
}
