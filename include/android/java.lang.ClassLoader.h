#pragma once

#include <black.jni.h>


namespace Android
{
inline namespace Java
{
inline namespace Lang
{
	// Handle for `java.lang.ClassLoader` objects.
	class ClassLoader : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's', 'L', 'o', 'a', 'd', 'e', 'r'>;

	// Construction and assignation.
	public:
		ClassLoader() = default;
		ClassLoader( jobject object_ref ) : Black::JniObject{ object_ref } {};
		ClassLoader( const ClassLoader& other ) : Black::JniObject( other ) {};
		ClassLoader( ClassLoader&& other ) : Black::JniObject( std::move( other ) ) {};


		const ClassLoader& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const ClassLoader& operator = ( const ClassLoader& other )	{ Black::JniObject::operator=( other ); return *this; };
		const ClassLoader& operator = ( ClassLoader&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };
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
	struct NativeContext<::Android::Java::Lang::ClassLoader> : public Black::NativeObjectContext<::Android::Java::Lang::ClassLoader>
	{

	};
}
}
}
}
