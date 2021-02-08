#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
	/**
		@breif	Custom JNI converter for `Black::JniClass` type.

		It implements the custom converting routine for objects of `Black::JniClass`. This type will be used by library to properly
		convert the class reference between C++ side and Java side.
	*/
	struct ClassHandleJniConverter final : Black::JniCommonTypeEnvContext<jobject>, Black::JniCommonTypeSignature<jclass>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr const size_t LOCAL_FRAME_SIZE = 1;


		// C++ native type.
		using NativeType	= Black::JniClass;

		// JNI type
		using JniType		= jclass;


		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination )	{ destination = source; };

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination )		{ destination = *source; };
	};
}
}
}
}
