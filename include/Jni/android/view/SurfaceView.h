#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.SurfaceView` objects.
	class SurfaceView final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'v', 'i', 'e', 'w', '/',
			'S', 'u', 'r', 'f', 'a', 'c', 'e', 'V', 'i', 'e', 'w'
		>;

	// Construction and assignation.
	public:
		SurfaceView() = default;
		SurfaceView( jobject object_ref ) : Black::JniObject{ object_ref } {};
		SurfaceView( const SurfaceView& other ) : Black::JniObject( other ) {};
		SurfaceView( SurfaceView&& other ) : Black::JniObject( std::move( other ) ) {};


		const SurfaceView& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const SurfaceView& operator = ( const SurfaceView& other )	{ Black::JniObject::operator=( other ); return *this; };
		const SurfaceView& operator = ( SurfaceView&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Call the `android.view.SurfaceView.getHolder` function.
		inline SufraceHolder GetHolder() const									{ return m_handles->get_holder.Call( *this ); };

		// Call the `android.view.SurfaceView.setSecure` function.
		inline void SetSecure( const bool is_secure ) const						{ if( m_handles->set_secure ){ m_handles->set_secure.Call( *this, is_secure ); } };

		// Call the `android.view.SurfaceView.setVisibility` function.
		inline void SetVisibility( const VisibilityState visibility ) const		{ m_handles->set_visibility.Call( *this, visibility ); };

		// Call the `android.view.SurfaceView.setZOrderMediaOverlay` function.
		inline void SetZorderMediaOverlay( const bool is_media_overlay ) const	{ m_handles->set_zorder_media_overlay.Call( *this, is_media_overlay ); };

		// Call the `android.view.SurfaceView.setZOrderOnTop` function.
		inline void SetZorderOnTop( const bool is_on_top ) const				{ m_handles->set_zorder_on_top.Call( *this, is_on_top ); };

	// Private state.
	private:
		struct SurfaceViewState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };

			Black::JniMemberFunction<SufraceHolder>			get_holder					{ class_handle, "getHolder" };
			Black::JniMemberFunction<void, bool>			set_secure					{ class_handle, "setSecure", Black::IGNORE_FALURE }; // Since android-17.
			Black::JniMemberFunction<void, VisibilityState>	set_visibility				{ class_handle, "setVisibility" };
			Black::JniMemberFunction<void, bool>			set_zorder_media_overlay	{ class_handle, "setZOrderMediaOverlay" };
			Black::JniMemberFunction<void, bool>			set_zorder_on_top			{ class_handle, "setZOrderOnTop" };
		};

		SharedState<SurfaceViewState> m_handles; // Shared JNI handles.
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
	// JNI context specification for handles to `android.view.SurfaceView` class.
	template<>
	struct NativeContext<::Jni::android::view::SurfaceView> : public Black::NativeObjectContext<::Jni::android::view::SurfaceView>
	{

	};
}
}
}
}
