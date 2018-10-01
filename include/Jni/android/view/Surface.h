#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.Surface` objects.
	class Surface final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'vi', 'e', 'w', '/', 'S', 'u', 'f', 'r', 'a', 'c', 'e'>;

	// Construction and assignation.
	public:
		Surface() = default;
		Surface( jobject object_ref ) : Black::JniObject{ object_ref } {};
		Surface( const Surface& other ) : Black::JniObject( other ) {};
		Surface( Surface&& other ) : Black::JniObject( std::move( other ) ) {};


		const Surface& operator = ( jobject object_ref )	{ Black::JniObject::operator=( object_ref ); return *this; };
		const Surface& operator = ( const Surface& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Surface& operator = ( Surface&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };
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
	// JNI context specification for handles to `android.view.Surface` class.
	template<>
	struct NativeContext<::Jni::android::view::Surface> : public Black::NativeObjectContext<::Jni::android::view::Surface>
	{

	};
}
}
}
}
