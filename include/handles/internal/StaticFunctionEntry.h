#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
	// Entry-point for JNI static function.
	template< typename TResult, typename... TArguments >
	class StaticFunctionEntry final : private Black::NonTransferable
	{
	// Construction and initialization.
	public:
		StaticFunctionEntry() = delete;
		inline StaticFunctionEntry( JNIEnv* local_env, jclass class_ref, jmethodID function_id );

	// Public interface.
	public:
		// Execute the bound function.
		inline TResult Call( const TArguments&... arguments ) const;

	// Private inner types.
	private:
		// Type of function result from JNI side.
		using JniResult = Black::JniType<TResult>;

		// JNI converter for given native type.
		using Converter = Black::JniNativeTypeConverter<TResult>;

	// Private static fields.
	private:
		// `JNIEnv` function handler to perform the call of the function with given type of result.
		static constexpr auto FUNCTION_HANDLER = Converter::STATIC_FUNCTION_HANDLER;

		// Logging channel.
		static constexpr const char* LOG_CHANNEL = "Black/Jni/StaticFunction/EntryPoint";

	// Private state.
	private:
		JNIEnv*		m_local_env;	// Current thread-local JNI environment.
		jclass		m_class_ref;	// JNI class reference.
		jmethodID	m_function_id;	// Id of function.
	};

	// Entry-point for JNI static function with void result.
	template< typename... TArguments >
	class StaticFunctionEntry<void, TArguments...> final : private Black::NonTransferable
	{
	// Construction and initialization.
	public:
		StaticFunctionEntry() = delete;
		inline StaticFunctionEntry( JNIEnv* local_env, jclass class_ref, jmethodID function_id );

	// Public interface.
	public:
		// Execute the bound function.
		inline void Call( const TArguments&... arguments ) const;

	// Private inner types.
	private:
		// JNI converter for given native type.
		using Converter	= Black::JniNativeTypeConverter<void>;

	// Private static fields.
	private:
		// `JNIEnv` function handler to perform the call of the function with given type of result.
		static constexpr auto FUNCTION_HANDLER = Converter::STATIC_FUNCTION_HANDLER;

		// Logging channel.
		static constexpr const char* LOG_CHANNEL = "Black/Jni/StaticFunction/EntryPoint";

	// Private state.
	private:
		JNIEnv*		m_local_env;	// Current thread-local JNI environment.
		jclass		m_class_ref;	// JNI class reference.
		jmethodID	m_function_id;	// Id of function.
	};
}
}
}
}
