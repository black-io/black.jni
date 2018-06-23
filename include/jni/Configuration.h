#pragma once


namespace Jni
{
inline namespace Android
{
inline namespace Context
{
inline namespace Res
{
	// Handle for `android.content.res.Configuration` objects.
	class Configuration final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'c', 'o', 'n', 't', 'e', 'n', 't', '/',
			'r', 'e', 's', '/',
			'C', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'a', 't', 'i', 'o', 'n'
		>;

	// Construction and assignation.
	public:
		Configuration() = default;
		Configuration( jobject object_ref ) : Black::JniObject{ object_ref } {};
		Configuration( const Configuration& other ) : Black::JniObject( other ) {};
		Configuration( Configuration&& other ) : Black::JniObject( std::move( other ) ) {};


		const Configuration& operator = ( jobject object_ref )			{ Black::JniObject::operator=( object_ref ); return *this; };
		const Configuration& operator = ( const Configuration& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Configuration& operator = ( Configuration&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// [since android-17] Getter for `android.content.res.Configuration.densityDpi` field.
		inline const int32_t GetDensityDpi() const						{ return m_handles->density_dpi.GetValue( *this, 0 ); };

		// Getter for `android.content.res.Configuration.fontScale` field.
		inline const float GetFontScale() const							{ return m_handles->font_scale.GetValue( *this, 0.0f ); };

		// Getter for `android.content.res.Configuration.keyboard` field.
		inline const KeyboardType GetKeyboardType() const				{ return m_handles->keyboard.GetValue( *this, KeyboardType::Undefined ); };

		// Getter for `android.content.res.Configuration.keyboardHidden` field.
		inline const KeyboardState GetKeyboardState() const				{ return m_handles->keyboard_hidden.GetValue( *this, KeyboardState::Undefined ); };

		// Platform-independent accessor to current locale.
		Jni::Locale GetLocale() const;

		// Getter for `android.content.res.Configuration.orientation` field.
		inline const ScreenOrientation GetOrientation() const			{ return m_handles->screen_orientation.GetValue( *this, ScreenOrientation::Undefined ); };

		// Getter for `android.content.res.Configuration.screenLayout` field.
		inline ScreenLayoutState GetScreenLayout() const				{ return m_handles->scren_layout.GetValue( *this, { 0 } ); };

		// Getter for `android.content.res.Configuration.screenWidthDp` field.
		inline const int32_t GetScreenWidthDp() const					{ return m_handles->scren_width_dp.GetValue( *this, 0 ); };

		// Getter for `android.content.res.Configuration.screenHeightDp` field.
		inline const int32_t GetScreenHeightDp() const					{ return m_handles->scren_height_dp.GetValue( *this, 0 ); };

		// Getter for `android.content.res.Configuration.smallestScreenWidthDp` field.
		inline const int32_t GetScreenSmallestWidthDp() const			{ return m_handles->scren_smallest_width_dp.GetValue( *this, 0 ); };

		// Getter for `android.content.res.Configuration.uiMode` field.
		inline ScreenUiMode GetUiMode() const							{ return m_handles->ui_mode.GetValue( *this, { 0 } ); };

	// Private state.
	private:
		struct ConfigurationState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };

			Black::JniMemberField<int32_t>				density_dpi				{ class_handle, "densityDpi", Black::IGNORE_FALURE }; // since android-17.
			Black::JniMemberField<float>				font_scale				{ class_handle, "fontScale" };
			Black::JniMemberField<KeyboardType>			keyboard				{ class_handle, "keyboard" };
			Black::JniMemberField<KeyboardState>		keyboard_hidden			{ class_handle, "keyboardHidden" };
			Black::JniMemberField<Jni::Locale>			locale					{ class_handle, "locale", Black::IGNORE_FALURE }; // till android-24
			Black::JniMemberField<ScreenOrientation>	screen_orientation		{ class_handle, "orientation" };
			Black::JniMemberField<ScreenLayoutState>	scren_layout			{ class_handle, "screenLayout" };
			Black::JniMemberField<int32_t>				scren_width_dp			{ class_handle, "screenWidthDp" };
			Black::JniMemberField<int32_t>				scren_height_dp			{ class_handle, "screenHeightDp" };
			Black::JniMemberField<int32_t>				scren_smallest_width_dp	{ class_handle, "smallestScreenWidthDp" };
			Black::JniMemberField<ScreenUiMode>			ui_mode					{ class_handle, "uiMode" };

			Black::JniMemberFunction<Jni::LocaleList>	get_locales				{ class_handle, "getLocales", Black::IGNORE_FALURE }; // since android-24
		};

		SharedState<ConfigurationState, true>	m_handles;	// Shared JNI handles.
	};
}
}
}
}


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	// JNI context specification for handles to `android.content.res.Configuration` class.
	template<>
	struct NativeContext<::Jni::Android::Context::Res::Configuration> : public Black::NativeObjectContext<::Jni::Android::Context::Res::Configuration>
	{

	};
}
}
}
}
