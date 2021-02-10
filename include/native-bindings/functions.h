#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace NativeBindings
{
	/**
		@brief	Build the information record for given native function.

		This function may be used to prepare the valid `JNINativeMethod` instance for the native function which uses only native types in signature.
		The function takes care about valid argument and result conversion between C++ and Java sides.
		Also the function constructs valid JNI-style signature for native function.

		All the user need to do is only pass the returned value into `Black::JniConnection::NativeBindingTable` initialization.

		@tparam	FUNCTION		The pointer to actual native function.
		@param	function_name	Java-side function name.
	*/
	template< auto FUNCTION >
	inline constexpr ::JNINativeMethod BuildNativeFunctionInfo( Black::NotNull<const char*> function_name );
}
}
}
