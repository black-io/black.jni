#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Translation of View visibility.
	enum class VisibilityState : int32_t
	{
		Visible		= 0x00,	// android.view.View.VISIBLE
		Invisible	= 0x04,	// android.view.View.INVISIBLE
		Gone		= 0x08,	// android.view.View.GONE
	};
}
}
}
