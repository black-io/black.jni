#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	// Static-field handle for JNI objects.
	template< typename TNativeType >
	class JniStaticField final
	{
		friend class Black::Jni::VirtualMachine::JniConnection;		// Grant access to function calls.
		friend class Black::Jni::VirtualMachine::JniEnvironment;	// Grant access to function calls.

	// Construction and assignment.
	public:
		JniStaticField()								= default;

		JniStaticField( const JniStaticField& other )	= default;
		JniStaticField( JniStaticField&& other )		= default;

		JniStaticField( Black::StringView class_name, Black::StringView field_name );
		JniStaticField( const Black::JniClass& class_handle, Black::StringView field_name );

		JniStaticField( Black::StringView class_name, Black::StringView field_name, Black::IgnoreFailure );
		JniStaticField( const Black::JniClass& class_handle, Black::StringView field_name, Black::IgnoreFailure );


		inline JniStaticField& operator = ( const JniStaticField& other )	= default;
		inline JniStaticField& operator = ( JniStaticField&& other )		= default;

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


		inline explicit operator const bool () const	{ return IsValid(); };
		inline jfieldID operator * () const				{ return GetFieldId(); };

	private:
		// JNI-side type for used native one.
		using JniType		= Black::JniType<TNativeType>;

		// JNI type signature.
		using Signature		= Black::NativeTypeSignature<TNativeType>;

		// JNI environment context.
		using JniContext	= Black::NativeTypeContext<TNativeType>;


		// Get the value of field.
		inline const bool GetValue( JNIEnv* local_env, TNativeType& value_storage ) const;

		// Set the value of field.
		inline const bool SetValue( JNIEnv* local_env, const TNativeType& value_storage ) const;

	private:
		static constexpr size_t	LOCAL_FRAME_SIZE	= JniContext::LOCAL_FRAME_SIZE;
		static constexpr auto	FIELD_READ_HANDLER	= JniContext::STATIC_FIELD_READ_HANDLER;
		static constexpr auto	FIELD_WRITE_HANDLER	= JniContext::STATIC_FIELD_WRITE_HANDLER;
		static constexpr char	LOG_CHANNEL[]		= "Black/Jni/StaticField";

		Black::JniClass	m_class_handle;				// Handle to class of field.
		jfieldID		m_field_id		= nullptr;	// Field id for JNI.
	};
}
}
}
