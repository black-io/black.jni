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
		@brief	Member-field handle for JNI objects.

		This template implements the functionality of accessing the field of some object.
		The field template should be instantiated for the type the field stores. Only native C++ types are allowed.
		The field automatically performs the conversion between C++ and Java types based on JNI type converter corresponded to native type.

		@tparam	TNativeType	Native C++ type the field stores.
	*/
	template< typename TNativeType >
	class JniMemberField final
	{
	// Construction and assignment.
	public:
		JniMemberField()						= default;
		JniMemberField( const JniMemberField& )	= default;
		JniMemberField( JniMemberField&& )		= default;

		JniMemberField( std::string_view class_name, std::string_view field_name );
		JniMemberField( const Black::JniClass& class_handle, std::string_view field_name );

		JniMemberField( std::string_view class_name, std::string_view field_name, Black::IgnoreFailure );
		JniMemberField( const Black::JniClass& class_handle, std::string_view field_name, Black::IgnoreFailure );


		inline JniMemberField& operator = ( const JniMemberField& )	= default;
		inline JniMemberField& operator = ( JniMemberField&& )		= default;

	// Public interface.
	public:
		// Get the value of field from given handle to object.
		inline const bool GetValue( const JniObject& object_handle, TNativeType& value_storage ) const;

		// Get the value of field from given object ref.
		inline const bool GetValue( jobject object_ref, TNativeType& value_storage ) const;

		// Get the value of field from given handle to object.
		inline TNativeType GetValue( const JniObject& object_handle, const TNativeType& default_value ) const;

		// Get the value of field from given object ref.
		inline TNativeType GetValue( jobject object_ref, const TNativeType& default_value ) const;


		// Set the value of field to given object by its handle.
		inline const bool SetValue( const JniObject& object_handle, const TNativeType& value_storage ) const;

		// Set the value of field to given object by its ref.
		inline const bool SetValue( jobject object_ref, const TNativeType& value_storage ) const;


		// Check the field handle carries valid value.
		inline const bool IsValid() const				{ return m_field_id != 0; };

		// Get the field id.
		inline jfieldID GetFieldId() const				{ return m_field_id; };


		inline jfieldID operator * () const				{ return GetFieldId(); };

		inline explicit operator const bool () const	{ return IsValid(); };
		inline const bool operator ! () const			{ return !IsValid(); };

	// Private interface.
	private:
		// JNI-side type for used native one.
		using JniType = Black::JniType<TNativeType>;

		// JNI type signature.
		using Signature = Black::JniTypeSignature<TNativeType>;

		// JNI environment context.
		using Converter = Black::JniNativeTypeConverter<TNativeType>;


		// Get the value of field from given object ref.
		inline const bool GetValue( JNIEnv* local_env, jobject object_ref, TNativeType& value_storage ) const;

		// Set the value of field to given object by its ref.
		inline const bool SetValue( JNIEnv* local_env, jobject object_ref, const TNativeType& value_storage ) const;

	// Private static fields.
	private:
		// Size of JNI local frame to hold the value reference.
		static constexpr size_t LOCAL_FRAME_SIZE = Converter::LOCAL_FRAME_SIZE;

		// `JNIEnv` field handler to read the value of field.
		static constexpr auto FIELD_READ_HANDLER = Converter::FIELD_READ_HANDLER;

		// `JNIEnv` field handler to write the value of field.
		static constexpr auto FIELD_WRITE_HANDLER = Converter::FIELD_WRITE_HANDLER;

		// Logging channel.
		static constexpr const char* LOG_CHANNEL = "Black/Jni/MemberField";

	// Private state.
	private:
		jfieldID m_field_id = nullptr; // Field id for JNI.
	};
}
}
}
}
