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
		// Cal the `android.view.ViewGroup.addView` function.
		inline void AddView( View child ) const;

		// Cal the `android.view.ViewGroup.addView` function.
		inline void AddView( View child, int32_t index ) const;

		// Cal the `android.view.ViewGroup.addView` function.
		inline void AddView( View child, LayoutParams params ) const;

		// Cal the `android.view.ViewGroup.addView` function.
		inline void AddView( View child, int32_t index, LayoutParams params ) const;

		// Cal the `android.view.ViewGroup.bringChildToFront` function.
		inline void BringChildToFront( View child ) const;

		// Cal the `android.view.ViewGroup.removeView` function.
		inline void RemoveView( View view ) const;

		// Cal the `android.view.ViewGroup.removeAllViews` function.
		inline void RemoveAllViews() const;

	// Private state.
	private:
		struct ViewGroupState;

		SharedState<ViewGroupState>	m_handles; // Shared JNI handles.
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
	// JNI context specification for handles to `android.view.ViewGroup` class.
	template<>
	struct NativeContext<::Jni::android::view::ViewGroup> : public Black::NativeObjectContext<::Jni::android::view::ViewGroup>
	{

	};
}
}
}
}
