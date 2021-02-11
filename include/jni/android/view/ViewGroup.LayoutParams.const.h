#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Translation of `android.view.ViewGroup.LayoutParams` constants.
	enum class LayoutParamsCode : int32_t
	{
		WrapContent	= -2,			// LayoutParams.WRAP_CONTENT	= -2
		MatchParent,				// LayoutParams.MATCH_PARENT	= -1
		FillParent	= MatchParent,	// LayoutParams.FILL_PARENT		= -1 - Deprecated since android-8.
	};
}
}
}
