#pragma once


namespace Jni
{
inline namespace android
{
inline namespace graphics
{
	inline const bool PixelFormat::HasAlpha( const PixelFormatCode format )
	{
		Black::JniStaticFunction<bool ( PixelFormatCode )> format_has_alpha{ Black::JniClass{ ClassPath::GetData() }, "formatHasAlpha" };

		return format_has_alpha.Call( format );
	}

	inline void PixelFormat::GetPixelFormatInfo( const PixelFormatCode format, const PixelFormat& info )
	{
		Black::JniStaticFunction<void ( PixelFormatCode, PixelFormat )> get_pixel_format_info { Black::JniClass{ ClassPath::GetData() }, "getPixelFormatInfo" };

		return get_pixel_format_info.Call( format, info );
	}
}
}
}
