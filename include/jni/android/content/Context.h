#pragma once


namespace Jni
{
inline namespace android
{
inline namespace content
{
	// Handle for `android.content.Context` objects.
	class Context final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<Context> GetJniConverter( Context );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'c', 'o', 'n', 't', 'e', 'n', 't', '/', 'C', 'o', 'n', 't', 'e', 'x', 't'>;

	// Construction and assignation.
	public:
		Context() = default;
		Context( jobject object_ref ) : Black::JniObject{ object_ref } {};
		Context( const Context& other ) : Black::JniObject( other ) {};
		Context( Context&& other ) : Black::JniObject( std::move( other ) ) {};


		const Context& operator = ( jobject object_ref )	{ Black::JniObject::operator=( object_ref ); return *this; };
		const Context& operator = ( const Context& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Context& operator = ( Context&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };
	};
}
}
}
