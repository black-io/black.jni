#pragma once


namespace Jni
{
inline namespace android
{
inline namespace content
{
inline namespace res
{
	// Translation of keyboard types.
	enum class KeyboardType : int32_t
	{
		Undefined		= ACONFIGURATION_KEYBOARD_ANY,			// android.content.res.Configuration.KEYBOARD_UNDEFINED
		None			= ACONFIGURATION_KEYBOARD_NOKEYS,		// android.content.res.Configuration.KEYBOARD_NOKEYS
		Qwerty			= ACONFIGURATION_KEYBOARD_QWERTY,		// android.content.res.Configuration.KEYBOARD_QWERTY
		PhoneStyle		= ACONFIGURATION_KEYBOARD_12KEY,		// android.content.res.Configuration.KEYBOARD_12KEY
	};

	// Translation of keyboard state.
	enum class KeyboardState : int32_t
	{
		Undefined		= ACONFIGURATION_KEYSHIDDEN_ANY,		// android.content.res.Configuration.KEYBOARDHIDDEN_UNDEFINED
		Exposed			= ACONFIGURATION_KEYSHIDDEN_NO,			// android.content.res.Configuration.KEYBOARDHIDDEN_NO
		Hiden			= ACONFIGURATION_KEYSHIDDEN_YES,		// android.content.res.Configuration.KEYBOARDHIDDEN_YES
		OnscreenExposed	= ACONFIGURATION_KEYSHIDDEN_SOFT,		// android.content.res.Configuration.???
	};

	// Translation of screen orientation.
	enum class ScreenOrientation : int32_t
	{
		Undefined		= ACONFIGURATION_ORIENTATION_ANY,		// android.content.res.Configuration.ORIENTATION_UNDEFINED
		Portrait		= ACONFIGURATION_ORIENTATION_PORT,		// android.content.res.Configuration.ORIENTATION_PORTRAIT
		Landscape		= ACONFIGURATION_ORIENTATION_LAND,		// android.content.res.Configuration.ORIENTATION_LANDSCAPE
		Square			= ACONFIGURATION_ORIENTATION_SQUARE,	// android.content.res.Configuration.ORIENTATION_SQUARE
	};
}
}
}
}
