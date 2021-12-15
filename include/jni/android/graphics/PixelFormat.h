#pragma once


namespace Jni
{
inline namespace android
{
inline namespace graphics
{
	// Handle for `android.graphics.PixelFormat` objects.
	class PixelFormat final : public Black::JniObject
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend JniConverter<PixelFormat> GetJniConverter( PixelFormat );

	// Public inner types.
	public:
		// Class path.
		using ClassPath = Black::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'v', 'i', 'e', 'w', '/', 'D', 'i', 's', 'p', 'l', 'a', 'y'>;

	// Public static interface.
	public:
		// Call the `android.graphics.PixelFormat.formatHasAlpha` function.
		static inline const bool HasAlpha( const PixelFormatCode format );

		// Call the `android.graphics.PixelFormat.getPixelFormatInfo` function.
		static inline void GetPixelFormatInfo( const PixelFormatCode format, const PixelFormat& info );

	// Construction and assignation.
	public:
		PixelFormat()							= default;
		PixelFormat( jobject object_ref )		: Black::JniObject{ object_ref } {};
		PixelFormat( const PixelFormat& other )	: Black::JniObject( other ) {};
		PixelFormat( PixelFormat&& other )		: Black::JniObject( std::move( other ) ) {};


		const PixelFormat& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const PixelFormat& operator = ( const PixelFormat& other )	{ Black::JniObject::operator=( other ); return *this; };
		const PixelFormat& operator = ( PixelFormat&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Getter for `android.graphics.PixelFormat.bitsPerPixel` field.
		inline const int32_t GetBitsPerPixel() const { return m_handles->bits_per_pixel.GetValue( *this, 0 ); };

		// Getter for `android.graphics.PixelFormat.bytesPerPixel` field.
		inline const int32_t GetBytsPerPixel() const { return m_handles->bytes_per_pixel.GetValue( *this, 0 ); };

	// Private inner types.
	private:
		struct ConfigurationState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };

			Black::JniMemberField<int32_t>	bits_per_pixel	{ class_handle, "bitsPerPixel" };
			Black::JniMemberField<int32_t>	bytes_per_pixel	{ class_handle, "bytesPerPixel" };
		};

	// Private state.
	private:
		ObjectState<ConfigurationState, true> m_handles; // Shared JNI handles.
	};
}
}
}
