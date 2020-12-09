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


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Internal
{
	// JNI context specification for `android.view.View.(VISIBLE|INVISIBLE|GONE)` constants group.
	template<>
	struct NativeContext<::Jni::android::view::VisibilityState> : public Black::NativeEnumContext<::Jni::android::view::VisibilityState>
	{

	};
}
}
}
}
