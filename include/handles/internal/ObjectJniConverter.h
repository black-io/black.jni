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
		@brief Custom JNI converter for any derived from `Black::JniObject` type.

		This template may be used to instantiate the custom converter. It simplifies the process of custom converter creation.

		@tparam	TObjectHandle	Type to be converted. Should be derived from `Black::JniObject` type.
	*/
	template< typename TObjectHandle >
	struct ObjectJniConverter final : Black::JniCommonTypeEnvContext<jobject>
	{
		static_assert( std::is_base_of_v<Black::JniObject, TObjectHandle>, "Type of object handle should be based on `Black::JniObject` type." );


		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t	LOCAL_FRAME_SIZE = 1;


		// JNI type signature.
		using Signature		= Black::StaticStringJoin<Black::StaticString<'L'>, typename TObjectHandle::ClassPath, Black::StaticString<';'>>;

		// C++ native type.
		using NativeType	= TObjectHandle;

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
