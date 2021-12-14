#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.WindowManager` objects.
	class WindowManager final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<WindowManager> GetJniConverter( WindowManager );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'v', 'i', 'e', 'w', '/',
			'W', 'i', 'n', 'd', 'o', 'w', 'M', 'a', 'n', 'a', 'g', 'e', 'r'
		>;

	// Construction and assignation.
	public:
		WindowManager() = default;
		WindowManager( jobject object_ref ) : Black::JniObject{ object_ref } {};
		WindowManager( const WindowManager& other ) : Black::JniObject( other ) {};
		WindowManager( WindowManager&& other ) : Black::JniObject( std::move( other ) ) {};


		const WindowManager& operator = ( jobject object_ref )	{ Black::JniObject::operator=( object_ref ); return *this; };
		const WindowManager& operator = ( const WindowManager& other )	{ Black::JniObject::operator=( other ); return *this; };
		const WindowManager& operator = ( WindowManager&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Call the `android.view.WindowManager.getDefaultDisplay` function.
		inline Display GetDefaultDisplay() const	{ return m_handles->get_default_display.Call( *this ); };

	// Private inner types.
	private:
		struct ConfigurationState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };

			Black::JniMemberFunction<Display ()>	get_default_display	{ class_handle, "getDefaultDisplay" };
		};

	// Private state.
	private:
		ObjectState<ConfigurationState, true> m_handles; // Shared JNI handles.
	};
}
}
}
