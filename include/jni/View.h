#pragma once


namespace Jni
{
inline namespace Android
{
inline namespace Views
{
	// Handle for `android.view.View` objects.
	class View final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'v', 'i', 'e', 'w', '/', 'V', 'i', 'e', 'w'>;

	// Construction and assignation.
	public:
		View() = default;
		View( jobject object_ref ) : Black::JniObject{ object_ref } {};
		View( const View& other ) : Black::JniObject( other ) {};
		View( View&& other ) : Black::JniObject( std::move( other ) ) {};


		const View& operator = ( jobject object_ref )	{ Black::JniObject::operator=( object_ref ); return *this; };
		const View& operator = ( const View& other )	{ Black::JniObject::operator=( other ); return *this; };
		const View& operator = ( View&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };
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
	struct NativeContext<::Jni::Android::Views::View> : public Black::NativeObjectContext<::Jni::Android::Views::View>
	{

	};
}
}
}
}

