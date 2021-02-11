#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.SurfaceHolder` objects.
	class SurfaceHolder final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<SurfaceHolder> GetJniConverter( SurfaceHolder );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'v', 'i', 'e', 'w', '/',
			'S', 'u', 'r', 'f', 'a', 'c', 'e', 'H', 'o', 'l', 'd', 'e', 'r'
		>;

	// Construction and assignation.
	public:
		SurfaceHolder() = default;
		SurfaceHolder( jobject object_ref ) : Black::JniObject{ object_ref } {};
		SurfaceHolder( const SurfaceHolder& other ) : Black::JniObject( other ) {};
		SurfaceHolder( SurfaceHolder&& other ) : Black::JniObject( std::move( other ) ) {};


		const SurfaceHolder& operator = ( jobject object_ref )			{ Black::JniObject::operator=( object_ref ); return *this; };
		const SurfaceHolder& operator = ( const SurfaceHolder& other )	{ Black::JniObject::operator=( other ); return *this; };
		const SurfaceHolder& operator = ( SurfaceHolder&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Call the `android.view.SurfaceHolder.addCallback` function.
		inline void AddCallback( const Callback& callback ) const;

		// Call the `android.view.SurfaceHolder.getSurface` function.
		inline Surface GetSurface() const;

		// Call the `android.view.SurfaceHolder.isCreating` function.
		inline const bool IsCreating() const;

		// Call the `android.view.SurfaceHolder.removeCallback` function.
		inline void RemoveCallback( const Callback& callback ) const;

		// Call the `android.view.SurfaceHolder.setFixedSize` function.
		inline void SetFixedSize( const int32_t width, const int32_t height ) const;

		// Call the `android.view.SurfaceHolder.setFormat` function.
		inline void SetFormat( const ::Jni::PixelFormatCode format ) const;

		// Call the `android.view.SurfaceHolder.setKeepScreenOn` function.
		inline void SetKeepSreenOn( const bool should_be_on ) const;

		// Call the `android.view.SurfaceHolder.setSizeFromLayout` function.
		inline void SetSizeFromLayout() const;

		// Call the `android.view.SurfaceHolder.setType` function. Deprecated since android-11.
		inline void SetType( const SurfaceType type ) const;

	// Private state.
	private:
		struct SurfaceHolderState;

		ObjectState<SurfaceHolderState> m_handles; // Shared JNI handles.
	};
}
}
}
