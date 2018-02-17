#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	// Static function handle for JNI classes.
	template< typename TResult, typename... TArguments >
	class JniStaticFunction final
	{
		friend class Black::Jni::VirtualMachine::JniConnection;		// Grant access to function calls.
		friend class Black::Jni::VirtualMachine::JniEnvironment;	// Grant access to function calls.

	// Construction and assignment.
	public:
		JniStaticFunction()									= default;

		JniStaticFunction( const JniStaticFunction& other )	= default;
		JniStaticFunction( JniStaticFunction&& other )		= default;

		JniStaticFunction( Black::StringView class_name, Black::StringView function_name );
		JniStaticFunction( const Black::JniClass& class_handle, Black::StringView function_name );

		JniStaticFunction( Black::StringView class_name, Black::StringView function_name, Black::IgnoreFailure );
		JniStaticFunction( const Black::JniClass& class_handle, Black::StringView function_name, Black::IgnoreFailure );


		inline JniStaticFunction& operator = ( const JniStaticFunction& other )	= default;
		inline JniStaticFunction& operator = ( JniStaticFunction&& other )		= default;

	// Public interface.
	public:
		// Call the function using given arguments.
		inline TResult Call( const TArguments&... arguments ) const;


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
		using EntryPoint	= Traits::StaticFunctionEntry<TResult, TArguments...>;


		// Call the function using given arguments and local JNI environment.
		inline TResult Call( JNIEnv* local_env, const TArguments&... arguments ) const;

	// Private state.
	private:
		static constexpr char	LOG_CHANNEL[]	= "Black/Jni/StaticFunction";

		Black::JniClass		m_class_handle;				// Handle to class owning the static method.
		jmethodID			m_function_id	= nullptr;	// Id of Java object method.
	};
}
}
}
