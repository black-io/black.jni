#pragma once


namespace Jni
{
inline namespace java
{
inline namespace lang
{
	// Handle for `java.lang.ClassLoader` objects.
	class ClassLoader final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<ClassLoader> GetJniConverter( ClassLoader );

	// Public inner types.
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
