#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
inline namespace Fields
{
	/**
		@brief	Static-field handle for JNI objects.

		This template implements the functionality of accessing the static field of some class.
		The field template should be instantiated for the type the field stores. Only native C++ types are allowed.
		The field automatically performs the conversion between C++ and Java types based on JNI type converter corresponded to native type.

		@tparam	TNativeType	Native C++ type the field stores.
	*/
	template< typename TNativeType >
	class JniStaticField final
	{
	// Construction and assignment.
	public:
		JniStaticField()						= default;
		JniStaticField( const JniStaticField& )	= default;
		JniStaticField( JniStaticField&& )		= default;

		JniStaticField( std::string_view class_name, std::string_view field_name );
		JniStaticField( const Black::JniClass& class_handle, std::string_view field_name );

		JniStaticField( std::string_view class_name, std::string_view field_name, Black::IgnoreFailure );
		JniStaticField( const Black::JniClass& class_handle, std::string_view field_name, Black::IgnoreFailure );


		inline JniStaticField& operator = ( const JniStaticField& )	= default;
		inline JniStaticField& operator = ( JniStaticField&& )		= default;

	// Public interface.
	public:
		// Get the value of field.
		inline const bool GetValue( TNativeType& value_storage ) const;

		// Get the value of field.
		inline TNativeType GetValue( const TNativeType& default_value ) const;

		// Set the value of field.
		inline const bool SetValue( const TNativeType& value_storage ) const;


		// Check the field handle is valid.
		inline const bool IsValid() const				{ return m_class_handle.IsValid() && ( m_field_id != 0 ); };

		// Get the field id.
		inline jfieldID GetFieldId() const				{ return m_field_id; };


		inline jfieldID operator * () const				{ return GetFieldId(); };

		inline explicit operator const bool () const	{ return IsValid(); };
		inline const bool operator ! () const			{ return !IsValid(); };

	// Private inner types.
	private:
		// JNI-side type for used native one.
		using JniType = Black::JniType<TNativeType>;

		// JNI type signature.
		using Signature = Black::JniTypeSignature<TNativeType>;

		// JNI converter for given native type.
		using Converter = Black::JniNativeTypeConverter<TNativeType>;

	// Private interface.
	private:
		// Get the value of field.
		inline const bool GetValue( JNIEnv* local_env, TNativeType& value_storage ) const;

		// Set the value of field.
		inline const bool SetValue( JNIEnv* local_env, const TNativeType& value_storage ) const;

	// Private static fields.
	private:
		// Size of JNI local frame to hold the value reference.
		static constexpr size_t LOCAL_FRAME_SIZE = Converter::LOCAL_FRAME_SIZE;

		// `JNIEnv` field handler to read the value of field.
		static constexpr auto FIELD_READ_HANDLER = Converter::STATIC_FIELD_READ_HANDLER;

		// `JNIEnv` field handler to write the value of field.
		static constexpr auto FIELD_WRITE_HANDLER = Converter::STATIC_FIELD_WRITE_HANDLER;

		// Logging channel.
		static constexpr const char* LOG_CHANNEL = "Black/Jni/StaticField";

	// Private state.
	private:
		Black::JniClass	m_class_handle;				// Handle to class of field.
		jfieldID		m_field_id		= nullptr;	// Field id for JNI.
	};
}
}
}
}
