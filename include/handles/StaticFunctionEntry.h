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
	public:
		StaticFunctionEntry() = delete;
		inline StaticFunctionEntry( JNIEnv* local_env, jclass class_ref, jmethodID function_id );

		// Execute the bound function.
		inline TResult Call( const TArguments&... arguments ) const;

	private:
		// Type of function result from JNI side.
		using JniResult		= Black::JniType<TResult>;

		// JNI environment context.
		using JniContext	= Black::NativeTypeContext<TResult>;

	private:
		static constexpr auto			FUNCTION_HANDLER	= JniContext::STATIC_FUNCTION_HANDLER;
		static constexpr const char*	LOG_CHANNEL			= "Black/Jni/StaticFunction/EntryPoint";

		JNIEnv*		m_local_env;	// Current thread-local JNI environment.
		jclass		m_class_ref;	// JNI class reference.
		jmethodID	m_function_id;	// Id of function.
	};

	// Entry-point for JNI static function with void result.
	template< typename... TArguments >
	class StaticFunctionEntry<void, TArguments...> final : private Black::NonTransferable
	{
	public:
		StaticFunctionEntry() = delete;
		inline StaticFunctionEntry( JNIEnv* local_env, jclass class_ref, jmethodID function_id );

		// Execute the bound function.
		inline void Call( const TArguments&... arguments ) const;

	private:
		// JNI environment context.
		using JniContext	= Black::NativeTypeContext<void>;

	private:
		static constexpr auto			FUNCTION_HANDLER	= JniContext::STATIC_FUNCTION_HANDLER;
		static constexpr const char*	LOG_CHANNEL			= "Black/Jni/StaticFunction/EntryPoint";

		JNIEnv*		m_local_env;	// Current thread-local JNI environment.
		jclass		m_class_ref;	// JNI class reference.
		jmethodID	m_function_id;	// Id of function.
	};
}
}
}
}
