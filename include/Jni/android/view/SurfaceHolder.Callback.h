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
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'v', 'i', 'e', 'w', '/',
			'S', 'u', 'f', 'r', 'a', 'c', 'e', 'H', 'o', 'l', 'd', 'e', 'r', '/',
			'C', 'a', 'l', 'l', 'b', 'a', 'c', 'k'
		>;

	// Construction and assignation.
	public:
		Callback() = default;
		Callback( jobject object_ref ) : Black::JniObject{ object_ref } {};
		Callback( const Callback& other ) : Black::JniObject( other ) {};
		Callback( Callback&& other ) : Black::JniObject( std::move( other ) ) {};


		const Callback& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const Callback& operator = ( const Callback& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Callback& operator = ( Callback&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };
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
	// JNI context specification for handles to `android.view.Callback` class.
	template<>
	struct NativeContext<::Jni::android::view::Callback> : public Black::NativeObjectContext<::Jni::android::view::Callback>
	{

	};
}
}
}
}
