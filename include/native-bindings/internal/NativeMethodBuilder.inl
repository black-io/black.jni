#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace NativeBindings
{
namespace Internal
{
	template< typename TSender, typename TResult, typename... TArguments >
	template< TResult (*NATIVE_HANDLER)( ::JNIEnv*, TSender, const TArguments&... ) >
	inline Black::JniType<TResult> NativeFunctionWrap<TSender, TResult, TArguments...>::Handle(
		::JNIEnv* local_env,
		TSender sender,
		Black::JniType<TArguments>... arguments
	)
	{
		return static_cast<Black::JniType<TResult>>( Black::ToJni<TResult>(
			NATIVE_HANDLER( local_env, sender, Black::FromJni<TArguments>( arguments )... )
		) );
	}

	template< typename TSender, typename... TArguments >
	template< void (*NATIVE_HANDLER)( ::JNIEnv*, TSender, const TArguments&... ) >
	inline void NativeFunctionWrap<TSender, void, TArguments...>::Handle( ::JNIEnv* local_env, TSender sender, Black::JniType<TArguments>... arguments )
	{
		NATIVE_HANDLER( local_env, sender, Black::FromJni<TArguments>( arguments )... );
	}

	template< typename TSender, typename TResult, typename... TArguments >
	template< TResult (*NATIVE_HANDLER)( ::JNIEnv*, TSender, const TArguments&... ) >
	constexpr ::JNINativeMethod NativeMethodBuilder<TResult (*)( ::JNIEnv*, TSender, const TArguments&... )>::Build( const char* const function_name )
	{
		constexpr auto wrapped_handler = &Wrap::template Handle<NATIVE_HANDLER>;
		return { function_name, Signature::GetData(), (void*)wrapped_handler };
	}
}
}
}
}
