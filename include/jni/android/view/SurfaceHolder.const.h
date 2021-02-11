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
