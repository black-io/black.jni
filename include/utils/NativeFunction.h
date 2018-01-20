#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
{
	// Specification for JNI native function handler.
	struct NativeFunction final
	{
		void*		address;	// Address of function.
		const char*	signature;	// Function signature.
		const char*	name;		// Function name.


		inline operator JNINativeMethod () const	{ return { name, signature, address }; };
	};
}


	// Native function handlers table for JNI class.
	struct NativeBindingTable final
	{
		const char*										class_name;	// JNI class path.
		std::initializer_list<Traits::NativeFunction>	natives;	// List of native handlers.
	};
}
}
}
