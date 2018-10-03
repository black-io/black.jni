#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Translation of `android.view.SurfaceHolder.SURFAC_TYPE_*` constants.
	enum class SurfaceType : int32_t
	{
		Normal = 0,		// Regular surface. Deprecated since android-11.
		Hardware,		// Hardware surface. Deprecated since android-5.
		Gpu,			// GPU-based surface. Deprecated since android-5.
		PushBuffers,	// Buffered surface. Deprecated since android-11.
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
	// JNI context specification for `android.view.SurfaceHolder.SURFAC_TYPE_` constants.
	template<>
	struct NativeContext<::Jni::android::view::SurfaceType> : public Black::NativeEnumContext<::Jni::android::view::SurfaceType>
	{

	};
}
}
}
}
