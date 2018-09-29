#pragma once


namespace Jni
{
inline namespace Android
{
inline namespace Contexts
{
	// Handle for `android.content.Context` objects.
	class Context final : public Black::JniObject
	{
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


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Internal
{
	// JNI context specification for handles to `android.content.Context` class.
	template<>
	struct NativeContext<::Jni::Android::Contexts::Context> : public Black::NativeObjectContext<::Jni::Android::Contexts::Context>
	{

	};
}
}
}
}
