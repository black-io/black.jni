#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	// Member-function handle for JNI objects.
	template< typename TResult, typename... TArguments >
	class JniMemberFunction final
	{
		friend class Black::Jni::VirtualMachine::JniEnvironment; // Grant access to function calls.

	// Construction and assignment.
	public:
		JniMemberFunction() = default;
		JniMemberFunction( const JniMemberFunction& other );
		JniMemberFunction( JniMemberFunction&& other );
		JniMemberFunction( Black::StringView class_name, Black::StringView funtion_name );
		JniMemberFunction( Black::StringView class_name, Black::StringView funtion_name, Black::IgnoreFailure );
		JniMemberFunction( const Black::JniClass& class_handle, Black::StringView funtion_name );
		JniMemberFunction( const Black::JniClass& class_handle, Black::StringView funtion_name, Black::IgnoreFailure );


		inline JniMemberFunction& operator = ( const JniMemberFunction& other );
		inline JniMemberFunction& operator = ( JniMemberFunction&& other );

	// Public interface.
	public:
		// Call the function for given object, using given arguments.
		inline TResult Call( const Black::JniObject& object_handle, const TArguments&... arguments ) const;

		// Call the non-virtual function for given object, using given arguments.
		inline TResult CallNonVirtual( const Black::JniObject& object_handle, const TArguments&... arguments ) const;


		// Check the field handle carries valid value.
		inline const bool IsValid() const				{ return m_function_id != 0; };

		// Get the function id.
		inline jmethodID GetFunctionId() const			{ return m_function_id; };

		// Get the signature of function.
		inline Black::StringView GetSignature() const	{ return { Signature::GetData(), Signature::GetLength() }; };


		inline explicit operator const bool () const	{ return IsValid(); };
		inline jmethodID operator * () const			{ return GetFunctionId(); };

	// Private interface.
	private:
		// JNI type signature.
		using Signature		= Black::NativeTypeSignature<TNativeType>;

		// Entry-point.
		using EntryPoint	= Traits::MemberFunctionEntry<TResult, TArguments...>;


		// Call the function for given object and local JNI environment, using given arguments.
		inline TResult Call( JNIEnv* local_env, jobject object_ref, const TArguments&... arguments ) const;

		// Call the non-virtual function for given object and local JNI environment, using given arguments.
		inline TResult CallNonVirtual( JNIEnv* local_env, jobject object_ref, const TArguments&... arguments ) const;

	// Private state.
	private:
		Class		m_class_handle;				// Handle to class owning the static method.
		jmethodID	m_function_id	= nullptr;	// Id of Java object method.
	};
}
}
}
