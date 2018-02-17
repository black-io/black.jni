#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
{
	template< typename TSender, typename TResult, typename... TArguments >
	template< TResult (*NATIVE_HANDLER)( JNIEnv*, TSender, const TArguments&... ) >
	Black::JniType<TResult> NativeFunctionWrap<TSender, TResult, TArguments...>::Handle(
		JNIEnv* local_env,
		TSender sender,
		Black::JniType<TArguments>... arguments
	)
	{
		return static_cast<Black::JniType<TResult>>( Black::ToJni<TResult>(
			NATIVE_HANDLER( local_env, sender, Black::FromJni<TArguments>( arguments )... )
		) );
	}

	template< typename TSender, typename... TArguments >
	template< void (*NATIVE_HANDLER)( JNIEnv*, TSender, const TArguments&... ) >
	void NativeFunctionWrap<TSender, void, TArguments...>::Handle( JNIEnv* local_env, TSender sender, Black::JniType<TArguments>... arguments )
	{
		NATIVE_HANDLER( local_env, sender, Black::FromJni<TArguments>( arguments )... );
	}

	template< typename TSender, typename TResult, typename... TArguments >
	template< TResult (*NATIVE_HANDLER)( JNIEnv*, TSender, const TArguments&... ) >
	constexpr NativeFunction NativeFunctionWrapper<TResult (*)( JNIEnv*, TSender, const TArguments&... )>::GetNativeFunction( const char* function_name )
	{
		constexpr auto wrapped_handler = &Wrap::template Handle<NATIVE_HANDLER>;
		return { (void*)wrapped_handler, Signature::GetData(), function_name };
	}
}
}
}
}
