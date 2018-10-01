#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.SufraceHolder` objects.
	class SufraceHolder final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'vi', 'e', 'w', '/',
			'S', 'u', 'f', 'r', 'a', 'c', 'e', 'H', 'o', 'l', 'd', 'e', 'r'
		>;

	// Construction and assignation.
	public:
		SufraceHolder() = default;
		SufraceHolder( jobject object_ref ) : Black::JniObject{ object_ref } {};
		SufraceHolder( const SufraceHolder& other ) : Black::JniObject( other ) {};
		SufraceHolder( SufraceHolder&& other ) : Black::JniObject( std::move( other ) ) {};


		const SufraceHolder& operator = ( jobject object_ref )			{ Black::JniObject::operator=( object_ref ); return *this; };
		const SufraceHolder& operator = ( const SufraceHolder& other )	{ Black::JniObject::operator=( other ); return *this; };
		const SufraceHolder& operator = ( SufraceHolder&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Call the `android.view.SufraceHolder.addCallback` function.
		inline void AddCallback( const Callback& callback ) const;

		// Call the `android.view.SufraceHolder.getSurface` function.
		inline Surface GetSurface() const;

		// Call the `android.view.SufraceHolder.isCreating` function.
		inline const bool IsCreating() const;

		// Call the `android.view.SufraceHolder.removeCallback` function.
		inline void RemoveCallback( const Callback& callback ) const;

		// Call the `android.view.SufraceHolder.setFixedSize` function.
		inline void SetFixedSize( const int32_t width, const int32_t height ) const;

		// Call the `android.view.SufraceHolder.setFormat` function.
		inline void SetFormat( const ::Jni::PixelFormatCode format ) const;

		// Call the `android.view.SufraceHolder.setKeepScreenOn` function.
		inline void SetKeepSreenOn( const bool should_be_on ) const;

		// Call the `android.view.SufraceHolder.setSizeFromLayout` function.
		inline void SetSizeFromLayout() const;

		// Call the `android.view.SufraceHolder.setType` function. Deprecated since android-11.
		inline void SetType( const SurfaceType type ) const;

	// Private state.
	private:
		struct SufraceHolderState;

		SharedState<SufraceHolderState> m_handles; // Shared JNI handles.
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
	// JNI context specification for handles to `android.view.SufraceHolder` class.
	template<>
	struct NativeContext<::Jni::android::view::SufraceHolder> : public Black::NativeObjectContext<::Jni::android::view::SufraceHolder>
	{

	};
}
}
}
}
