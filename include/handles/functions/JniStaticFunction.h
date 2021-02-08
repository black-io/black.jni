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
		@brief	JNI static function handle.

		This template implements the functionality of calling the static functions of some class.
		The function template should be instantiated for the valid function signature, where only native C++ types present.
		This handle automatically converts all given arguments on call.
		The result of Java call will be also automatically converted back to native type, when required.

		@tparam	TFunction Valid function signature.
	*/
	template< typename TFunction >
	class JniStaticFunction;

	// Static function handle for JNI classes.
	template< typename TResult, typename... TArguments >
	class JniStaticFunction<TResult (TArguments...)> final
	{
	// Construction and assignment.
	public:
		JniStaticFunction()								= default;
		JniStaticFunction( const JniStaticFunction& )	= default;
		JniStaticFunction( JniStaticFunction&& )		= default;

		JniStaticFunction( std::string_view class_name, std::string_view function_name );
		JniStaticFunction( const Black::JniClass& class_handle, std::string_view function_name );

		JniStaticFunction( std::string_view class_name, std::string_view function_name, Black::IgnoreFailure );
		JniStaticFunction( const Black::JniClass& class_handle, std::string_view function_name, Black::IgnoreFailure );


		inline JniStaticFunction& operator = ( const JniStaticFunction& )	= default;
		inline JniStaticFunction& operator = ( JniStaticFunction&& )		= default;

	// Public interface.
	public:
		// Call the function using given arguments.
		inline TResult Call( const TArguments&... arguments ) const;


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
		using EntryPoint = Internal::StaticFunctionEntry<TResult, TArguments...>;

	// Private interface.
	private:
		// Call the function using given arguments and local JNI environment.
		inline TResult Call( JNIEnv* local_env, const TArguments&... arguments ) const;

	// Private static fields.
	private:
		// Logging channel.
		static constexpr const char* LOG_CHANNEL = "Black/Jni/StaticFunction";

	// Private state.
	private:
		Black::JniClass	m_class_handle;				// Handle to class owning the static method.
		jmethodID		m_function_id	= nullptr;	// Id of Java object method.
	};
}
}
}
}
