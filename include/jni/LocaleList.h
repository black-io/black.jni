#pragma once


namespace Jni
{
inline namespace Android
{
inline namespace Os
{
	// Handle for `android.os.LocaleList` objects.
	class LocaleList final : Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'o', 's', '/', 'L', 'o', 'c', 'a', 'l', 'e', 'L', 'i', 's', 't'>;

	// Construction and assignation.
	public:
		LocaleList() = default;
		LocaleList( jobject object_ref ) : Black::JniObject{ object_ref } {};
		LocaleList( const LocaleList& other ) : Black::JniObject( other ) {};
		LocaleList( LocaleList&& other ) : Black::JniObject( std::move( other ) ) {};


		const LocaleList& operator = ( jobject object_ref )			{ Black::JniObject::operator=( object_ref ); return *this; };
		const LocaleList& operator = ( const LocaleList& other )	{ Black::JniObject::operator=( other ); return *this; };
		const LocaleList& operator = ( LocaleList&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Call of `android.os.LocaleList.isEmpty` function.
		inline const bool IsEmpty() const							{ return m_handles->is_empty.Call( *this ); };

		// Call of `android.os.LocaleList.size` function.
		inline const int32_t GetSize() const						{ return m_handles->get_size.Call( *this ); };

		// Call of `android.os.LocaleList.get` function.
		inline Locale GetLocale( const int32_t index ) const		{ return m_handles->get_locale.Call( *this, index ); };

	// Private state.
	private:
		struct LocaleListState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };

			Black::JniMemberFunction<bool>				is_empty	{ class_handle, "isEmpty" };
			Black::JniMemberFunction<int32_t>			get_size	{ class_handle, "size" };
			Black::JniMemberFunction<Locale, int32_t>	get_locale	{ class_handle, "get" };
		};

		SharedState<LocaleListState>	m_handles; // Shared JNI handles.
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
	// JNI context specification for handles to `android.os.LocaleList` class.
	template<>
	struct NativeContext<::Jni::Android::Os::LocaleList> : public Black::NativeObjectContext<::Jni::Android::Os::LocaleList>
	{

	};
}
}
}
}
