#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.ViewGroup` objects.
	class ViewGroup final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<ViewGroup> GetJniConverter( ViewGroup );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'v', 'i', 'e', 'w', '/', 'V', 'i', 'e', 'w', 'G', 'r', 'o', 'u', 'p'>;

	// Construction and assignation.
	public:
		ViewGroup() = default;
		ViewGroup( jobject object_ref ) : Black::JniObject{ object_ref } {};
		ViewGroup( const ViewGroup& other ) : Black::JniObject( other ) {};
		ViewGroup( ViewGroup&& other ) : Black::JniObject( std::move( other ) ) {};


		const ViewGroup& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const ViewGroup& operator = ( const ViewGroup& other )	{ Black::JniObject::operator=( other ); return *this; };
		const ViewGroup& operator = ( ViewGroup&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Call the `android.view.ViewGroup.addView` function.
		inline void AddView( const View& child ) const;

		// Call the `android.view.ViewGroup.addView` function.
		inline void AddView( const View& child, const int32_t index ) const;

		// Call the `android.view.ViewGroup.addView` function.
		inline void AddView( const View& child, const LayoutParams& params ) const;

		// Call the `android.view.ViewGroup.addView` function.
		inline void AddView( const View& child, const int32_t index, const LayoutParams& params ) const;

		// Call the `android.view.ViewGroup.bringChildToFront` function.
		inline void BringChildToFront( const View& child ) const;

		// Call the `android.view.ViewGroup.removeView` function.
		inline void RemoveView( const View& view ) const;

		// Call the `android.view.ViewGroup.removeAllViews` function.
		inline void RemoveAllViews() const;

	// Private state.
	private:
		struct ViewGroupState;

		ObjectState<ViewGroupState>	m_handles; // Shared JNI handles.
	};
}
}
}
