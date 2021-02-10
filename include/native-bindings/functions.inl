#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace NativeBindings
{
	template< auto FUNCTION >
	inline constexpr ::JNINativeMethod BuildNativeFunctionInfo( Black::NotNull<const char*> function_name )
	{
		return Internal::NativeMethodBuilder<decltype( FUNCTION )>::template Build<FUNCTION>( function_name );
	}
}
}
}
