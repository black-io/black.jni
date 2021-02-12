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
		@brief	Custom JNI converter for `Black::JniObject` type.

		It implements the custom converting routine for objects of `Black::JniObject`. This type will be used by library to properly
		convert the class reference between C++ side and Java side.
	*/
	struct ObjectHandleJniConverter final : Black::JniCommonTypeEnvContext<jobject>, Black::JniCommonTypeSignature<jobject>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr const size_t LOCAL_FRAME_SIZE = 1;


		// C++ native type.
		using NativeType	= Black::JniObject;

		// JNI type
		using JniType		= jobject;


		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination )	{ destination = source; };

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination )		{ destination = *source; };
	};
}
}
}
}
