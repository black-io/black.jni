#pragma once


namespace Jni
{
inline namespace android
{
inline namespace os
{
	// Handle for `android.os.Bundle` objects.
	class Bundle final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<Bundle> GetJniConverter( Bundle );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'o', 's', '/', 'B', 'u', 'n', 'd', 'l', 'e'>;

	// Construction and assignation.
	public:
		Bundle() = default;
		Bundle( jobject object_ref ) : Black::JniObject{ object_ref } {};
		Bundle( const Bundle& other ) : Black::JniObject( other ) {};
		Bundle( Bundle&& other ) : Black::JniObject( std::move( other ) ) {};


		const Bundle& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const Bundle& operator = ( const Bundle& other )	{ Black::JniObject::operator=( other ); return *this; };
		const Bundle& operator = ( Bundle&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:

	// Private inner types.
	private:
		// Shared state of handle.
		struct BundleState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };
		};

	// Private state.
	private:
		ObjectState<BundleState> m_handles; // Shared JNI handles.
	};
}
}
}
