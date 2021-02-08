#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
	// Entry-point for JNI member function.
	template< typename TResult, typename... TArguments >
	class MemberFunctionEntry final : private Black::NonTransferable
	{
	// Construction and initialization.
	public:
		MemberFunctionEntry() = delete;
		inline MemberFunctionEntry( JNIEnv* local_env, jobject object_ref, jmethodID function_id );

	// Public interface.
	public:
		// Execute the bound function using regular virtual invocation.
		inline TResult Call( const TArguments&... arguments ) const;

		// Execute the bound function directly from class of object.
		inline TResult CallNonVirtual( jclass class_ref, const TArguments&... arguments ) const;

	// Private inner types.
	private:
		// Type of function result from JNI side.
		using JniResult = Black::JniType<TResult>;

		// JNI converter for given native type.
		using Converter = Black::JniNativeTypeConverter<TResult>;

	// Private static fields.
	private:
		// `JNIEnv` function handler to perform the virtual call of the function with given type of result.
		static constexpr auto FUNCTION_HANDLER = Converter::FUNCTION_HANDLER;

		// `JNIEnv` function handler to perform the non-virtual call of the function with given type of result.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER = Converter::NONVIRTUAL_FUNCTION_HANDLER;

		// Logging channel.
		static constexpr const char* LOG_CHANNEL = "Black/Jni/MemberFunction/EntryPoint";

	// Private state.
	private:
		JNIEnv*		m_local_env;	// Current thread-local JNI environment.
		jmethodID	m_function_id;	// Id of function.
		jobject		m_object_ref;	// Reference to Java object.
	};

	// Entry-point for JNI member function with void result.
	template< typename... TArguments >
	class MemberFunctionEntry<void, TArguments...> final : private Black::NonTransferable
	{
	// Construction and initialization.
	public:
		MemberFunctionEntry() = delete;
		inline MemberFunctionEntry( JNIEnv* local_env, jobject object_ref, jmethodID function_id );

	// Public interface.
	public:
		// Execute the bound function using regular virtual invocation.
		inline void Call( const TArguments&... arguments ) const;

		// Execute the bound function directly from class of object.
		inline void CallNonVirtual( jclass class_ref, const TArguments&... arguments ) const;

	// Private inner types.
	private:
		// JNI converter for given native type.
		using Converter	= Black::JniNativeTypeConverter<void>;

	// Private static fields.
	private:
		// `JNIEnv` function handler to perform the virtual call of the function with given type of result.
		static constexpr auto FUNCTION_HANDLER = Converter::FUNCTION_HANDLER;

		// `JNIEnv` function handler to perform the non-virtual call of the function with given type of result.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER = Converter::NONVIRTUAL_FUNCTION_HANDLER;

		// Logging channel.
		static constexpr const char* LOG_CHANNEL = "Black/Jni/MemberFunction/EntryPoint";

	// Private state.
	private:
		JNIEnv*		m_local_env;	// Current thread-local JNI environment.
		jmethodID	m_function_id;	// Id of function.
		jobject		m_object_ref;	// Reference to Java object.
	};
}
}
}
}
