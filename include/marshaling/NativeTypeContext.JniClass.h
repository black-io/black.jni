#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	// JNI environment context for `Black::JniClass` type.
	template<>
	struct NativeContext<Black::JniClass> : JniContext<jobject>, JniSignature<jobject>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

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
