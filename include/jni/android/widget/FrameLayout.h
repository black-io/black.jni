#pragma once


namespace Jni
{
inline namespace android
{
inline namespace widget
{
	// Handle for `android.widget.FrameLayout` objects.
	class FrameLayout final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<FrameLayout> GetJniConverter( FrameLayout );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'w', 'i', 'd', 'g', 'e', 't', '/',
			'F', 'r', 'a', 'm', 'e', 'L', 'a', 'y', 'o', 'u', 't'
		>;

	// Construction and assignation.
	public:
		FrameLayout() = default;
		FrameLayout( jobject object_ref ) : Black::JniObject{ object_ref } {};
		FrameLayout( const FrameLayout& other ) : Black::JniObject( other ) {};
		FrameLayout( FrameLayout&& other ) : Black::JniObject( std::move( other ) ) {};


		const FrameLayout& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const FrameLayout& operator = ( const FrameLayout& other )	{ Black::JniObject::operator=( other ); return *this; };
		const FrameLayout& operator = ( FrameLayout&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };
	};
}
}
}
