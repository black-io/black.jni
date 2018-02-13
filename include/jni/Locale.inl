#pragma once


namespace Jni
{
inline namespace Java
{
inline namespace Util
{
	struct Locale::LocaleState final
	{
		Black::JniClass	class_handle{ ClassPath::GetData() };

		Black::JniMemberFunction<std::string>			get_country				{ class_handle,	"getCountry" };
		Black::JniMemberFunction<std::string>			get_display_country		{ class_handle,	"getDisplayCountry" };
		Black::JniMemberFunction<std::string>			get_display_lang		{ class_handle,	"getDisplayLanguage" };
		Black::JniMemberFunction<std::string>			get_display_name		{ class_handle,	"getDisplayName" };
		Black::JniMemberFunction<std::string>			get_display_script		{ class_handle,	"getDisplayScript" };
		Black::JniMemberFunction<std::string>			get_display_variant		{ class_handle,	"getDisplayVariant" };
		Black::JniMemberFunction<std::string, Locale>	get_display_country_for	{ class_handle,	"getDisplayCountry" };
		Black::JniMemberFunction<std::string, Locale>	get_display_lang_for	{ class_handle,	"getDisplayLanguage" };
		Black::JniMemberFunction<std::string, Locale>	get_display_name_for	{ class_handle,	"getDisplayName" };
		Black::JniMemberFunction<std::string, Locale>	get_display_script_for	{ class_handle,	"getDisplayScript" };
		Black::JniMemberFunction<std::string, Locale>	get_display_variant_for	{ class_handle,	"getDisplayVariant" };
		Black::JniMemberFunction<std::string>			get_language			{ class_handle,	"getLanguage" };
		Black::JniMemberFunction<std::string>			get_script				{ class_handle,	"getScript" };
		Black::JniMemberFunction<std::string>			get_variant				{ class_handle,	"getVariant" };
	};


	inline std::string Locale::GetCountry() const
	{
		return m_handles->get_country.Call( *this );
	}

	inline std::string Locale::GetLanguage() const
	{
		return m_handles->get_language.Call( *this );
	}

	inline std::string Locale::GetScript() const
	{
		return m_handles->get_script.Call( *this );
	}

	inline std::string Locale::GetVariant() const
	{
		return m_handles->get_variant.Call( *this );
	}

	inline std::string Locale::GetDisplayCountry() const
	{
		return m_handles->get_display_country.Call( *this );
	}

	inline std::string Locale::GetDisplayLanguage() const
	{
		return m_handles->get_display_lang.Call( *this );
	}

	inline std::string Locale::GetDisplayName() const
	{
		return m_handles->get_display_name.Call( *this );
	}

	inline std::string Locale::GetDisplayScript() const
	{
		return m_handles->get_display_script.Call( *this );
	}

	inline std::string Locale::GetDisplayVariant() const
	{
		return m_handles->get_display_variant.Call( *this );
	}

	inline std::string Locale::GetDisplayCountry( const Locale& other ) const
	{
		return m_handles->get_display_country_for.Call( *this, other );
	}

	inline std::string Locale::GetDisplayLanguage( const Locale& other ) const
	{
		return m_handles->get_display_lang_for.Call( *this, other );
	}

	inline std::string Locale::GetDisplayName( const Locale& other ) const
	{
		return m_handles->get_display_name_for.Call( *this, other );
	}

	inline std::string Locale::GetDisplayScript( const Locale& other ) const
	{
		return m_handles->get_display_script_for.Call( *this, other );
	}

	inline std::string Locale::GetDisplayVariant( const Locale& other ) const
	{
		return m_handles->get_display_variant_for.Call( *this, other );
	}
}
}
}
