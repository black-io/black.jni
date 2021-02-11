#pragma once


namespace Jni
{
inline namespace android
{
inline namespace graphics
{
	// Translation of `android.graphics.PixelFormat` constants.
	enum class PixelFormatCode : int32_t
	{
		Translucent		= -3,		// PixelFormat.TRANSLUCENT	= -3;
		Transparent,				// PixelFormat.TRANSPARENT	= -2;
		Opaque,						// PixelFormat.OPAQUE		= -1;
		Unknon,						// PixelFormat.UNKNOWN		= 0;
		RGBA_8888,					// PixelFormat.RGBA_8888	= 1;
		RGBX_8888,					// PixelFormat.RGBX_8888	= 2;
		RGB_888,					// PixelFormat.RGB_888		= 3;
		RGB_565,					// PixelFormat.RGB_565		= 4;
		RGBA_5551		= 0x06,		// PixelFormat.RGBA_5551	= 6;
		RGBA_4444,					// PixelFormat.RGBA_4444	= 7;
		A_8,						// PixelFormat.A_8			= 8;
		L_8,						// PixelFormat.L_8			= 9;
		LA_88,						// PixelFormat.LA_88		= 0xA;
		RGB_332,					// PixelFormat.RGB_332		= 0xB;
		YCbCr_422_SP	= 0x10,		// PixelFormat.YCbCr_422_SP	= 0x10;
		YCbCr_420_SP,				// PixelFormat.YCbCr_420_SP	= 0x11;
		YCbCr_422_I		= 0x14,		// PixelFormat.YCbCr_422_I	= 0x14;
		RGBA_F16		= 0x16,		// PixelFormat.RGBA_F16		= 0x16;
		RGBA_1010102	= 0x2B,		// PixelFormat.RGBA_1010102	= 0x2B;
		JPEG			= 0x0100,	// PixelFormat.JPEG			= 0x100;
	};
}
}
}
