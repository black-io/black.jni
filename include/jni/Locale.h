#pragma once


namespace Jni
{
inline namespace Java
{
inline namespace Util
{
	// Handle for `java.util.Locale` objects.
	class Locale final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<'j', 'a', 'v', 'a', '/', 'u', 't', 'i', 'l', '/', 'L', 'o', 'c', 'a', 'l', 'e'>;

	// Construction and assignation.
	public:
		Locale() = default;
		Locale( jobject object_ref ) : Black::JniObject{ object_ref } {};
		Locale( const Locale& other ) : Black::JniObject( other ) {};
		Locale( Locale&& other ) : Black::JniObject( std::move( other ) ) {};


		const Locale& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const Locale& operator = ( const Locale& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Locale& operator = ( Locale&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Call the `java.util.Locale.getCountry` function.
		inline std::string GetCountry() const;

		// Call the `java.util.Locale.getLanguage` function.
		inline std::string GetLanguage() const;

		// Call the `java.util.Locale.getScript` function.
		inline std::string GetScript() const;

		// Call the `java.util.Locale.getVariant` function.
		inline std::string GetVariant() const;

		// Call the `java.util.Locale.getDisplayCountry` function.
		inline std::string GetDisplayCountry() const;

		// Call the `java.util.Locale.getDisplayLanguage` function.
		inline std::string GetDisplayLanguage() const;

		// Call the `java.util.Locale.getDisplayName` function.
		inline std::string GetDisplayName() const;

		// Call the `java.util.Locale.getDisplayScript` function.
		inline std::string GetDisplayScript() const;

		// Call the `java.util.Locale.getDisplayVariant` function.
		inline std::string GetDisplayVariant() const;

		// Call the `java.util.Locale.getDisplayCountry` function.
		inline std::string GetDisplayCountry( const Locale& other ) const;

		// Call the `java.util.Locale.getDisplayLanguage` function.
		inline std::string GetDisplayLanguage( const Locale& other ) const;

		// Call the `java.util.Locale.getDisplayName` function.
		inline std::string GetDisplayName( const Locale& other ) const;

		// Call the `java.util.Locale.getDisplayScript` function.
		inline std::string GetDisplayScript( const Locale& other ) const;

		// Call the `java.util.Locale.getDisplayVariant` function.
		inline std::string GetDisplayVariant( const Locale& other ) const;

	// Private state.
	private:
		// The external declaration is forced by necessary of using the `Locale` class itself as well-defined one.
		struct LocaleState;

		SharedState<LocaleState>	m_handles;	// Shared JNI handles.
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
namespace Traits
{
	// JNI context specification for handles to `java.util.Locale` class.
	template<>
	struct NativeContext<::Jni::Java::Util::Locale> : public Black::NativeObjectContext<::Jni::Java::Util::Locale>
	{

	};
}
}
}
}
