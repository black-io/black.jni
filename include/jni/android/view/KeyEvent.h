#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Handle for `android.view.KeyEvent` objects.
	class KeyEvent final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'v', 'i', 'e', 'w', '/', 'K', 'e', 'y', 'E', 'v', 'e', 'n', 't'>;

	// Construction and assignation.
	public:
		KeyEvent() = default;
		KeyEvent( jobject object_ref ) : Black::JniObject{ object_ref } {};
		KeyEvent( const KeyEvent& other ) : Black::JniObject( other ) {};
		KeyEvent( KeyEvent&& other ) : Black::JniObject( std::move( other ) ) {};


		const KeyEvent& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const KeyEvent& operator = ( const KeyEvent& other )	{ Black::JniObject::operator=( other ); return *this; };
		const KeyEvent& operator = ( KeyEvent&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Call of `android.view.KeyEvent.getCharacters` function.
		inline std::string GetChars() const						{ return m_handles->get_chars.Call( *this ); };

		// Call of `android.view.KeyEvent.getDisplayLabel` function.
		inline char16_t GetLabel() const						{ return m_handles->get_label.Call( *this ); };

		// Call of `android.view.KeyEvent.getDownTime` function.
		inline std::chrono::milliseconds GetDownTime() const	{ return std::chrono::milliseconds{ m_handles->get_down_time.Call( *this ) }; };

		// Call of `android.view.KeyEvent.getEventTime` function.
		inline std::chrono::milliseconds GetEventTime() const	{ return std::chrono::milliseconds{ m_handles->get_event_time.Call( *this ) }; };

		// Call of `android.view.KeyEvent.getKeyCode` function.
		inline const int32_t GetKeyCode() const					{ return m_handles->get_key_code.Call( *this ); };

		// Call of `android.view.KeyEvent.getMetaState` function.
		inline Jni::KeyMetaState GetMetaState() const			{ return m_handles->get_meta_state.Call( *this ); };

		// Call of `android.view.KeyEvent.getRepeatCount` function.
		inline int32_t GetScanCode() const						{ return m_handles->get_scan_code.Call( *this ); };

	// Private state.
	private:
		struct KeyEventState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };

			Black::JniMemberFunction<std::string>		get_chars		{ class_handle,	"getCharacters" };
			Black::JniMemberFunction<char16_t>			get_label		{ class_handle,	"getDisplayLabel" };
			Black::JniMemberFunction<int64_t>			get_down_time	{ class_handle,	"getDownTime" };
			Black::JniMemberFunction<int64_t>			get_event_time	{ class_handle,	"getEventTime" };
			Black::JniMemberFunction<int32_t>			get_key_code	{ class_handle,	"getKeyCode" };
			Black::JniMemberFunction<Jni::KeyMetaState>	get_meta_state	{ class_handle,	"getMetaState" };
			Black::JniMemberFunction<int32_t>			get_scan_code	{ class_handle,	"getRepeatCount" };
		};

		SharedState<KeyEventState, true>	m_handles;	// Shared JNI handles.
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
	// JNI context specification for handles to `android.view.KeyEvent` class.
	template<>
	struct NativeContext<::Jni::android::view::KeyEvent> : public Black::NativeObjectContext<::Jni::android::view::KeyEvent>
	{

	};
}
}
}
}
