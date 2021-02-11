#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.ViewGroup.LayoutParams` objects.
	class LayoutParams final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<LayoutParams> GetJniConverter( LayoutParams );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'v', 'i', 'e', 'w', '/',
			'V', 'i', 'e', 'w', 'G', 'r', 'o', 'u', 'p', '$', 'L', 'a', 'y', 'o', 'u', 't', 'P', 'a', 'r', 'a', 'm', 's'
		>;

	// Construction and assignation.
	public:
		LayoutParams() = default;
		LayoutParams( jobject object_ref ) : Black::JniObject{ object_ref } {};
		LayoutParams( const LayoutParams& other ) : Black::JniObject( other ) {};
		LayoutParams( LayoutParams&& other ) : Black::JniObject( std::move( other ) ) {};


		const LayoutParams& operator = ( jobject object_ref )			{ Black::JniObject::operator=( object_ref ); return *this; };
		const LayoutParams& operator = ( const LayoutParams& other )	{ Black::JniObject::operator=( other ); return *this; };
		const LayoutParams& operator = ( LayoutParams&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };
	};
}
}
}
