#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Traits
{
	// Entry-point for JNI member function.
	template< typename TResult, typename... TArguments >
	class MemberFunctionEntry
	{
	public:
		inline MemberFunctionEntry( JNIEnv* local_env, jobject object_ref, jmethodID function_id );

		// Execute the bound function using regular virtual invocation.
		inline TResult Call( const TArguments&... arguments ) const;

		// Execute the bound function directly from class of object.
		inline TResult CallNonVirtual( const TArguments&... arguments ) const;

	private:
		// Type of function result from JNI side.
		using JniResult = Black::JniType<TResult>;

		// JNI environment context.
		using JniContext	= Black::NativeTypeContext<TNativeType>;

	private:
		constexpr static auto FUNCTION_HANDLER				= JniContext::FUNCTION_HANDLER;
		constexpr static auto NONVIRTUAL_FUNCTION_HANDLER	= JniContext::NONVIRTUAL_FUNCTION_HANDLER;

		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jmethodID	m_function_id	= nullptr;	// Id of function.
		jobject		m_object_ref	= nullptr;	// Reference to Java object.
	};

	// Entry-point for JNI member function with void result.
	template< typename... TArguments >
	class MemberFunctionEntry< void, TArguments... >
	{
	public:
		inline MemberFunctionEntry( JNIEnv* local_env, jobject object_ref, jmethodID function_id );

		// Execute the bound function using regular virtual invocation.
		inline void Call( const TArguments&... arguments ) const;

		// Execute the bound function directly from class of object.
		inline void CallNonVirtual( const TArguments&... arguments ) const;

	private:
		// JNI environment context.
		using JniContext	= Black::NativeTypeContext<void>;

	private:
		constexpr static auto FUNCTION_HANDLER				= JniContext::FUNCTION_HANDLER;
		constexpr static auto NONVIRTUAL_FUNCTION_HANDLER	= JniContext::NONVIRTUAL_FUNCTION_HANDLER;

		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jmethodID	m_function_id	= nullptr;	// Id of function.
		jobject		m_object_ref	= nullptr;	// Reference to Java object.
	};
}
}
}
}
