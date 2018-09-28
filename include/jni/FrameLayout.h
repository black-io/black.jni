#pragma once


namespace Jni
{
inline namespace Android
{
inline namespace Widget
{
	class FrameLayout final : public Jni::View
	{
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
		FrameLayout( jobject object_ref ) : Jni::View{ object_ref } {};
		FrameLayout( const FrameLayout& other ) : Jni::View( other ) {};
		FrameLayout( FrameLayout&& other ) : Jni::View( std::move( other ) ) {};


		const FrameLayout& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const FrameLayout& operator = ( const FrameLayout& other )	{ Black::JniObject::operator=( other ); return *this; };
		const FrameLayout& operator = ( FrameLayout&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };
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
	// JNI context specification for handles to `android.view.View` class.
	template<>
	struct NativeContext<::Jni::Android::Widget::FrameLayout> : public Black::NativeObjectContext<::Jni::Android::Widget::FrameLayout>
	{

	};
}
}
}
}
