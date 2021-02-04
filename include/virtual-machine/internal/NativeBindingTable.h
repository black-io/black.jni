#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
	// Native function handlers table for JNI class.
	struct NativeBindingTable final
	{
		const char*										class_name;	// JNI class path.
		std::initializer_list<Internal::NativeFunction>	natives;	// List of native handlers.
	};
}
}
}
