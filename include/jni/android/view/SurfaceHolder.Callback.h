#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.SurfaceHolder.Callback` objects.
	class Callback final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<Callback> GetJniConverter( Callback );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'v', 'i', 'e', 'w', '/',
			'S', 'u', 'r', 'f', 'a', 'c', 'e', 'H', 'o', 'l', 'd', 'e', 'r', '$', 'C', 'a', 'l', 'l', 'b', 'a', 'c', 'k'
		>;

	// Construction and assignation.
	public:
		Callback() = default;
		Callback( jobject object_ref ) : Black::JniObject{ object_ref } {};
		Callback( const Callback& other ) : Black::JniObject( other ) {};
		Callback( Callback&& other ) : Black::JniObject( std::move( other ) ) {};


		const Callback& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const Callback& operator = ( const Callback& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Callback& operator = ( Callback&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };
	};
}
}
}
