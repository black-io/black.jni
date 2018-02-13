#include <jni.android.content.res.Configuration.h>


namespace Jni
{
inline namespace Android
{
inline namespace Context
{
inline namespace Res
{
	Jni::Locale Configuration::GetLocale() const
	{
		// When running on platforms below 24, the `locale` field will be valid.
		CRET( m_handles->locale, m_handles->locale.GetValue( *this, {} ) );

		// For 24+ platform the `get_locales` function will be valid.
		auto locales = m_handles->get_locales.Call( *this );
		CRET( locales.IsEmpty(), {} );

		return locales.GetLocale( 0 );
	}
}
}
}
}
