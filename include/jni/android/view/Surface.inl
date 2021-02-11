#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	struct Surface::SurfaceState final
	{
		Black::JniClass class_handle{ ClassPath::GetData() };

		Black::JniMemberFunction<bool ()>	is_valid	{ class_handle, "isValid" };
		Black::JniMemberFunction<void ()>	release		{ class_handle, "release" };
	};


	inline const bool Surface::IsSurfaceValid() const
	{
		return m_handles->is_valid.Call( *this );
	}

	inline void Surface::Release() const
	{
		return m_handles->release.Call( *this );
	}

	inline ANativeWindow* Surface::GetNativeWindow() const
	{
		return m_window;
	}
}
}
}
