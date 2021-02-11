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
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<Surface> GetJniConverter( Surface );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'v', 'i', 'e', 'w', '/', 'S', 'u', 'r', 'f', 'a', 'c', 'e'>;

	// Construction and assignation.
	public:
		Surface() = default;
		Surface( jobject object_ref );
		Surface( const Surface& other );
		Surface( Surface&& other );


		const Surface& operator = ( jobject object_ref );
		const Surface& operator = ( const Surface& other );
		const Surface& operator = ( Surface&& other );

	// Public interface.
	public:
		// Call the `android.view.Surface.isValid` function.
		inline const bool IsSurfaceValid() const;

		// Call the `android.view.Surface.release` function.
		inline void Release() const;


		// Get the native window interface.
		inline ANativeWindow* GetNativeWindow() const;

	// Private interface.
	private:
		void AcquireNativeWindow();

	// Private state.
	private:
		struct SurfaceState;

		ANativeWindow*					m_window	= nullptr;	// Pointer to native window.
		ObjectState<SurfaceState, true>	m_handles;				// Shared JNI handles.
	};
}
}
}
