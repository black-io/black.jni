#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
	template< auto FUNCTION >
	inline ::JNINativeMethod JniConnection::BuildNativeFunctionInfo( Black::NotNull<const char*> function_name )
	{
		return Internal::NativeMethodBuilder<decltype( FUNCTION )>::template Build<FUNCTION>( function_name );
	}
}
}
}
