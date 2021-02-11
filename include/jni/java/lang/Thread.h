#pragma once


namespace Jni
{
inline namespace java
{
inline namespace lang
{
	// Handle for `java.lang.Thread` objects.
	class Thread final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<Thread> GetJniConverter( Thread );

	// Public inner types.
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
