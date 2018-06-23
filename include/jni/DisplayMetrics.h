#pragma once


namespace Jni
{
inline namespace Android
{
inline namespace Util
{
	// Handle for `android.util.DisplayMetrics` objects.
	class DisplayMetrics final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'u', 't', 'i', 'l', '/',
			'D', 'i', 's', 'p', 'l', 'a', 'y', 'M', 'e', 't', 'r', 'i', 'c', 's'
		>;

	// Construction and assignation.
	public:
		DisplayMetrics() = default;
		DisplayMetrics( jobject object_ref ) : Black::JniObject{ object_ref } {};
		DisplayMetrics( const DisplayMetrics& other ) : Black::JniObject( other ) {};
		DisplayMetrics( DisplayMetrics&& other ) : Black::JniObject( std::move( other ) ) {};


		const DisplayMetrics& operator = ( jobject object_ref )				{ Black::JniObject::operator=( object_ref ); return *this; };
		const DisplayMetrics& operator = ( const DisplayMetrics& other )	{ Black::JniObject::operator=( other ); return *this; };
		const DisplayMetrics& operator = ( DisplayMetrics&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Getter for `android.util.DisplayMetrics.density` field.
		inline const float GetDensity() const								{ return m_handles->density.GetValue( *this, 0.0f ); };

		// Getter for `android.util.DisplayMetrics.densityDpi` field.
		inline const int32_t GetDensityDpi() const							{ return m_handles->density_dpi.GetValue( *this, 0 ); };

		// Getter for `android.util.DisplayMetrics.scaledDensity` field.
		inline const float GetScaldDensity() const							{ return m_handles->scaled_density.GetValue( *this, 0.0f ); };

		// Getter for `android.util.DisplayMetrics.widthPixels` field.
		inline const int32_t GetWidth() const								{ return m_handles->width_pixels.GetValue( *this, 0 ); };

		// Getter for `android.util.DisplayMetrics.heightPixels` field.
		inline const int32_t GetHeight() const								{ return m_handles->height_pixels.GetValue( *this, 0 ); };

		// Getter for `android.util.DisplayMetrics.xdpi` field.
		inline const float GetWidthDpi() const								{ return m_handles->width_dpi.GetValue( *this, 0.0f ); };

		// Getter for `android.util.DisplayMetrics.ydpi` field.
		inline const float GetHeightDpi() const								{ return m_handles->height_dpi.GetValue( *this, 0.0f ); };

	// Private state.
	private:
		struct DisplayMetricsState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };

			Black::JniMemberField<float>	density			{ class_handle,	"density" };
			Black::JniMemberField<int32_t>	density_dpi		{ class_handle,	"densityDpi" };
			Black::JniMemberField<float>	scaled_density	{ class_handle,	"scaledDensity" };
			Black::JniMemberField<int32_t>	width_pixels	{ class_handle,	"widthPixels" };
			Black::JniMemberField<int32_t>	height_pixels	{ class_handle,	"heightPixels" };
			Black::JniMemberField<float>	width_dpi		{ class_handle,	"xdpi" };
			Black::JniMemberField<float>	height_dpi		{ class_handle,	"ydpi" };
		};

		SharedState<DisplayMetricsState>	m_handles;
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
	// JNI context specification for handles to `android.util.DisplayMetrics` class.
	template<>
	struct NativeContext<::Jni::Android::Util::DisplayMetrics> : public Black::NativeObjectContext<::Jni::Android::Util::DisplayMetrics>
	{

	};
}
}
}
}
