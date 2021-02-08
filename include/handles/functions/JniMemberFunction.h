#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
inline namespace Functions
{
	/**
		@brief	JNI member-function handle.

		This template implements the functionality of calling the member-functions of some class.
		The function template should be instantiated for the valid function signature, where only native C++ types present.
		This handle automatically converts all given arguments on call.
		The result of Java call will be also automatically converted back to native type, when required.

		@tparam	TFunction Valid function signature.
	*/
	template< typename TFunction >
	class JniMemberFunction;

	// Member-function handle for JNI objects.
	template< typename TResult, typename... TArguments >
	class JniMemberFunction<TResult (TArguments...)> final
	{
	// Construction and assignment.
	public:
		JniMemberFunction()								= default;
		JniMemberFunction( const JniMemberFunction& )	= default;
		JniMemberFunction( JniMemberFunction&& )		= default;

		JniMemberFunction( std::string_view class_name, std::string_view function_name );
		JniMemberFunction( const Black::JniClass& class_handle, std::string_view function_name );

		JniMemberFunction( std::string_view class_name, std::string_view function_name, Black::IgnoreFailure );
		JniMemberFunction( const Black::JniClass& class_handle, std::string_view function_name, Black::IgnoreFailure );


		inline JniMemberFunction& operator = ( const JniMemberFunction& )	= default;
		inline JniMemberFunction& operator = ( JniMemberFunction&& )		= default;

	// Public interface.
	public:
		// Call the function for given object, using given arguments.
		inline TResult Call( const Black::JniObject& object_handle, const TArguments&... arguments ) const;

		// Call the function for given object, using given arguments.
		inline TResult Call( Black::NotNull<jobject> object_ref, const TArguments&... arguments ) const;

		// Call the non-virtual function for given object, using given arguments.
		inline TResult CallNonVirtual( const Black::JniObject& object_handle, const TArguments&... arguments ) const;

		// Call the non-virtual function for given object, using given arguments.
		inline TResult CallNonVirtual( Black::NotNull<jobject> object_ref, const TArguments&... arguments ) const;


		// Check the field handle carries valid value.
		inline const bool IsValid() const				{ return m_function_id != 0; };

		// Get the function id.
		inline jmethodID GetFunctionId() const			{ return m_function_id; };

		// Get the signature of function.
		inline std::string_view GetSignature() const	{ return { Signature::GetData(), Signature::GetLength() }; };


		inline jmethodID operator * () const			{ return GetFunctionId(); };

		inline explicit operator const bool () const	{ return IsValid(); };
		inline const bool operator ! () const			{ return !IsValid(); };

	// Private inner types.
	private:
		// JNI type signature.
		using Signature = Black::NativeFunctionSignature<TResult, TArguments...>;

		// Entry-point.
		using EntryPoint = Internal::MemberFunctionEntry<TResult, TArguments...>;

	// Private interface.
	private:
		// Call the function for given object and local JNI environment, using given arguments.
		inline TResult Call( JNIEnv* local_env, jobject object_ref, const TArguments&... arguments ) const;

		// Call the non-virtual function for given object and local JNI environment, using given arguments.
		inline TResult CallNonVirtual( JNIEnv* local_env, jobject object_ref, const TArguments&... arguments ) const;

	// Private static fields.
	private:
		// Logging channel.
		static constexpr const char* LOG_CHANNEL = "Black/Jni/MemberFunction";

	// Private state.
	private:
		Black::JniClass	m_class_handle;				// Handle to class owning the static method.
		jmethodID		m_function_id	= nullptr;	// Id of Java object method.
	};
}
}
}
}
