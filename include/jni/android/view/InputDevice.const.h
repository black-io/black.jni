#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Translation of input device class.
	enum class InputSourceClass : int32_t
	{
		None		= AINPUT_SOURCE_CLASS_NONE,			// android.view.InputDevice.SOURCE_CLASS_NONE
		Button		= AINPUT_SOURCE_CLASS_BUTTON,		// android.view.InputDevice.SOURCE_CLASS_BUTTON
		Pointer		= AINPUT_SOURCE_CLASS_POINTER,		// android.view.InputDevice.SOURCE_CLASS_POINTER
		Navigation	= AINPUT_SOURCE_CLASS_NAVIGATION,	// android.view.InputDevice.SOURCE_CLASS_TRACKBALL
		Position	= AINPUT_SOURCE_CLASS_POSITION,		// android.view.InputDevice.SOURCE_CLASS_POSITION
		Joystick	= AINPUT_SOURCE_CLASS_JOYSTICK,		// android.view.InputDevice.SOURCE_CLASS_JOYSTICK
	};
}
}
}
