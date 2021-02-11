#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace NativeBindings
{
namespace Internal
{
	// JNI native function wrap. It used to wrap the native implementation into JNI-consumable type.
	template< typename TSender, typename TResult, typename... TArguments >
	struct NativeFunctionWrap final
	{
		// JNI-consumable style for given native implementation.
		template< TResult (*NATIVE_HANDLER)( ::JNIEnv*, TSender, const TArguments&... ) >
		static inline Black::JniType<TResult> Handle( ::JNIEnv* local_env, TSender sender, Black::JniType<TArguments>... arguments );
	};

	// JNI native function wrap. It used to wrap the native implementation into JNI-consumable type.
	template< typename TSender, typename... TArguments >
	struct NativeFunctionWrap<TSender, void, TArguments...> final
	{
		// JNI-consumable style for given native implementation.
		template< void (*NATIVE_HANDLER)( ::JNIEnv*, TSender, const TArguments&... ) >
		static inline void Handle( ::JNIEnv* local_env, TSender sender, Black::JniType<TArguments>... arguments );
	};


	// JNI native function wrapper. It help to wrap the native implementation into JNI-consumable type.
	template< typename TFunction >
	struct NativeMethodBuilder;

	// Specification for true native functions.
	template< typename TSender, typename TResult, typename... TArguments >
	struct NativeMethodBuilder<TResult (*)( ::JNIEnv*, TSender, const TArguments&... )> final
	{
		// Suppress the possible wrong declaration of native function.
		static_assert( std::is_same_v<jobject, TSender> || std::is_same_v<jclass, TSender>, "The sender class may be only `jclass` or `jobject`." );


		// Function signature.
		using Signature	= Black::JniTypeFunctionSignature<TResult, TArguments...>;

		// Type of function wrap.
		using Wrap		= NativeFunctionWrap<TSender, TResult, TArguments...>;


		// Perform the build of native method information.
		template< TResult (*NATIVE_HANDLER)( ::JNIEnv*, TSender, const TArguments&... ) >
		static constexpr ::JNINativeMethod Build( const char* const function_name );
	};
}
}
}
}
