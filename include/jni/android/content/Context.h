#pragma once


namespace Jni
{
inline namespace android
{
inline namespace content
{
	// Handle for `android.content.Context` objects.
	class Context final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<Context> GetJniConverter( Context );

	// Public inner types.
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

	// Public interface.
	public:
		// Getter for `android.content.Context.DISPLAY_SERVICE` field.
		inline std::string GetDisplayServiceName() const							{ return m_handles->display_service.GetValue( {} ); };

		// Getter for `android.content.Context.WINDOW_SERVICE` field.
		inline std::string GetWindowServiceName() const								{ return m_handles->window_service.GetValue( {} ); };


		// Call the `android.content.Context.getSystemService` function.
		inline Black::JniObject GetSystemService( const std::string& name ) const	{ return m_handles->get_system_service.Call( *this, name ); };

	// Private inner types.
	private:
		struct ConfigurationState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };

			Black::JniStaticField<std::string>							display_service		{ class_handle, "DISPLAY_SERVICE" };
			Black::JniStaticField<std::string>							window_service		{ class_handle, "WINDOW_SERVICE" };

			Black::JniMemberFunction<Black::JniObject ( std::string )>	get_system_service	{ class_handle, "getSystemService" };
		};

	// Private state.
	private:
		ObjectState<ConfigurationState, true> m_handles; // Shared JNI handles.
	};
}
}
}
