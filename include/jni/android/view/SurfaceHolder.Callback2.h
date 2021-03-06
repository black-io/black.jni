#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.SurfaceHolder.Callback2` objects.
	class Callback2 final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<Callback2> GetJniConverter( Callback2 );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'v', 'i', 'e', 'w', '/',
			'S', 'u', 'r', 'f', 'a', 'c', 'e', 'H', 'o', 'l', 'd', 'e', 'r', '$', 'C', 'a', 'l', 'l', 'b', 'a', 'c', 'k', '2'
		>;

	// Construction and assignation.
	public:
		Callback2() = default;
		Callback2( jobject object_ref ) : Black::JniObject{ object_ref } {};
		Callback2( const Callback2& other ) : Black::JniObject( other ) {};
		Callback2( Callback2&& other ) : Black::JniObject( std::move( other ) ) {};


		const Callback2& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const Callback2& operator = ( const Callback2& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Callback2& operator = ( Callback2&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };
	};
}
}
}
