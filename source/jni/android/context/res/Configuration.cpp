#include <jni.android.content.res.Configuration.h>


namespace Jni
{
inline namespace android
{
inline namespace context
{
inline namespace res
{
	Jni::Locale Configuration::GetLocale() const
	{
		// When running on platforms below 24, the `locale` field will be valid.
		CRET( m_handles->locale.IsValid(), m_handles->locale.GetValue( *this, {} ) );

		ENSURES_DEBUG( m_handles->get_locales.IsValid() );

		// For 24+ platform the `get_locales` function will be valid.
		auto locales = m_handles->get_locales.Call( *this );
		CRET( !locales.IsValid() || locales.IsEmpty(), {} );

		return locales.GetLocale( 0 );
	}
}
}
}
}
