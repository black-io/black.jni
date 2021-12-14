#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.Display` objects.
	class Display final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<Display> GetJniConverter( Display );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'v', 'i', 'e', 'w', '/', 'D', 'i', 's', 'p', 'l', 'a', 'y'>;

	// Construction and assignation.
	public:
		Display()						= default;
		Display( jobject object_ref )	: Black::JniObject{ object_ref } {};
		Display( const Display& other )	: Black::JniObject( other ) {};
		Display( Display&& other )		: Black::JniObject( std::move( other ) ) {};


		const Display& operator = ( jobject object_ref )	{ Black::JniObject::operator=( object_ref ); return *this; };
		const Display& operator = ( const Display& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Display& operator = ( Display&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Call the `android.view.Display.getRealMetrics` function.
		inline void GetRealMetrics( const DisplayMetrics& metrics ) const	{ m_handles->get_real_metrics.Call( *this, metrics ); };

		// Call the `android.view.Display.getRefreshRate` function.
		inline const float GetRefreshRate() const							{ m_handles->get_refresh_rate.Call( *this ); };

	// Private inner types.
	private:
		struct ConfigurationState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };

			Black::JniMemberFunction<void ( DisplayMetrics )>	get_real_metrics	{ class_handle, "getRealMetrics" };
			Black::JniMemberFunction<float ()>					get_refresh_rate	{ class_handle, "getRefreshRate" };
		};

	// Private state.
	private:
		ObjectState<ConfigurationState, true> m_handles; // Shared JNI handles.
	};
}
}
}
