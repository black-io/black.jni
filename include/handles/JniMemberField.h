#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	// Member-field handle for JNI objects.
	template< typename TNativeType >
	class JniMemberField final
	{
		friend class Black::Jni::VirtualMachine::JniConnection;		// Grant access to function calls.
		friend class Black::Jni::VirtualMachine::JniEnvironment;	// Grant access to function calls.

	// Construction and assignment.
	public:
		JniMemberField()								= default;

		JniMemberField( const JniMemberField& other )	= default;
		JniMemberField( JniMemberField&& other )		= default;

		JniMemberField( Black::StringView class_name, Black::StringView field_name );
		JniMemberField( const Black::JniClass& class_handle, Black::StringView field_name );

		JniMemberField( Black::StringView class_name, Black::StringView field_name, Black::IgnoreFailure );
		JniMemberField( const Black::JniClass& class_handle, Black::StringView field_name, Black::IgnoreFailure );


		inline JniMemberField& operator = ( const JniMemberField& other )	= default;
		inline JniMemberField& operator = ( JniMemberField&& other )		= default;

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


		inline explicit operator const bool () const	{ return IsValid(); };
		inline jfieldID operator * () const				{ return GetFieldId(); };

	// Private interface.
	private:
		// JNI-side type for used native one.
		using JniType		= Black::JniType<TNativeType>;

		// JNI type signature.
		using Signature		= Black::NativeTypeSignature<TNativeType>;

		// JNI environment context.
		using JniContext	= Black::NativeTypeContext<TNativeType>;


		// Get the value of field from given object ref.
		inline const bool GetValue( JNIEnv* local_env, jobject object_ref, TNativeType& value_storage ) const;

		// Set the value of field to given object by its ref.
		inline const bool SetValue( JNIEnv* local_env, jobject object_ref, const TNativeType& value_storage ) const;

	private:
		static constexpr size_t			LOCAL_FRAME_SIZE	= JniContext::LOCAL_FRAME_SIZE;
		static constexpr auto			FIELD_READ_HANDLER	= JniContext::FIELD_READ_HANDLER;
		static constexpr auto			FIELD_WRITE_HANDLER	= JniContext::FIELD_WRITE_HANDLER;
		static constexpr const char*	LOG_CHANNEL			= "Black/Jni/MemberField";

		jfieldID	m_field_id	= nullptr;	// Field id for JNI.
	};
}
}
}
