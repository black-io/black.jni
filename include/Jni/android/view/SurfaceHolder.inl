#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	struct SufraceHolder::SufraceHolderState final
	{
		Black::JniClass	class_handle{ ClassPath::GetData() };

		Black::JniMemberFunction<void, Callback>				add_callback			{ class_handle, "addCallback" };
		Black::JniMemberFunction<Surface>						get_surface				{ class_handle, "getSurface" };
		Black::JniMemberFunction<bool>							is_creating				{ class_handle, "isCreating" };
		Black::JniMemberFunction<void, Callback>				remove_callback			{ class_handle, "removeCallback" };
		Black::JniMemberFunction<void, int32_t, int32_t>		set_fixed_size			{ class_handle, "setFixedSize" };
		Black::JniMemberFunction<void, ::Jni::PixelFormatCode>	set_format				{ class_handle, "setFormat" };
		Black::JniMemberFunction<void, bool>					set_keep_screen_on		{ class_handle, "setKeepScreenOn" };
		Black::JniMemberFunction<void>							set_size_from_layout	{ class_handle, "setSizeFromLayout" };
		Black::JniMemberFunction<void, SurfaceType>				set_type				{ class_handle, "setType", Black::IGNORE_FALURE };
	};

	inline void SufraceHolder::AddCallback( const Callback& callback ) const
	{
		m_handles->add_callback.Call( *this, callback );
	}

	inline Surface SufraceHolder::GetSurface() const
	{
		return m_handles->get_surface.Call( *this );
	}

	inline const bool SufraceHolder::IsCreating() const
	{
		return m_handles->is_creating.Call( *this );
	}

	inline void SufraceHolder::RemoveCallback( const Callback& callback ) const
	{
		m_handles->remove_callback.Call( *this, callback );
	}

	inline void SufraceHolder::SetFixedSize( const int32_t width, const int32_t height ) const
	{
		m_handles->set_fixed_size.Call( *this, width, height );
	}

	inline void SufraceHolder::SetFormat( const ::Jni::PixelFormatCode format ) const
	{
		m_handles->set_format.Call( *this, format );
	}

	inline void SufraceHolder::SetKeepSreenOn( const bool should_be_on ) const
	{
		m_handles->set_keep_screen_on.Call( *this, should_be_on );
	}

	inline void SufraceHolder::SetSizeFromLayout() const
	{
		m_handles->set_size_from_layout.Call( *this );
	}

	inline void SufraceHolder::SetType( const SurfaceType type ) const
	{
		CRET( !m_handles->set_type );
		m_handles->set_type.Call( *this, type );
	}
}
}
}
