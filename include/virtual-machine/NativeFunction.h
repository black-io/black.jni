#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Internal
{
	// Specification for JNI native function handler.
	struct NativeFunction final
	{
		void*		address;	// Address of function.
		const char*	signature;	// Function signature.
		const char*	name;		// Function name.


		inline operator JNINativeMethod () const	{ return { name, signature, address }; };
	};

	// JNI native function wrap. It used to wrap the native implementation into JNI-consumable type.
	template< typename TSender, typename TResult, typename... TArguments >
	struct NativeFunctionWrap final
	{
		// JNI-consumable style for given native implementation.
		template< TResult (*NATIVE_HANDLER)( JNIEnv*, TSender, const TArguments&... ) >
		static Black::JniType<TResult> Handle( JNIEnv* local_env, TSender sender, Black::JniType<TArguments>... arguments );
	};

	// JNI native function wrap. It used to wrap the native implementation into JNI-consumable type.
	template< typename TSender, typename... TArguments >
	struct NativeFunctionWrap<TSender, void, TArguments...> final
	{
		// JNI-consumable style for given native implementation.
		template< void (*NATIVE_HANDLER)( JNIEnv*, TSender, const TArguments&... ) >
		static void Handle( JNIEnv* local_env, TSender sender, Black::JniType<TArguments>... arguments );
	};

	// JNI native function wrapper. It help to wrap the native implementation into JNI-consumable type.
	template< typename TFunction >
	struct NativeFunctionWrapper;

	// Specification for true native functions.
	template< typename TSender, typename TResult, typename... TArguments >
	struct NativeFunctionWrapper<TResult (*)( JNIEnv*, TSender, const TArguments&... )> final
	{
		// Suppress the possible wrong declaration of native function.
		static_assert( std::is_same_v<jobject, TSender> || std::is_same_v<jclass, TSender>, "The sender class may be only `jclass` or `jobject`." );

		// Function signature.
		using Signature	= Black::NativeFunctionSignature<TResult, TArguments...>;

		// Type of function wrap.
		using Wrap		= NativeFunctionWrap<TSender, TResult, TArguments...>;

		// Get the native function for some function handler.
		template< TResult (*NATIVE_HANDLER)( JNIEnv*, TSender, const TArguments&... ) >
		static constexpr NativeFunction GetNativeFunction( const char* function_name );
	};
}

	// Get the JNI native function for some handler.
	template< typename TFunction, TFunction FUNCTION_HANDLER >
	constexpr Internal::NativeFunction MakeNativeFunction( const char* function_name )
	{
		return Internal::NativeFunctionWrapper<TFunction>::template GetNativeFunction<FUNCTION_HANDLER>( function_name );
	}
}
}
}


// Simplifying macro to make the native function construction more comfortable.
#define BLACK_JNI_NATIVE_FUNCTION( NAME, FUNC )	Black::MakeNativeFunction<decltype( FUNC ), FUNC>( NAME )
