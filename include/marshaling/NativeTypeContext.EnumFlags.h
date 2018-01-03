#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	// JNI environment context for `Black::EnumFlags` type.
	template< typename TEnumeration >
	struct NativeContext<Black::EnumFlags<TEnumeration>> : NativeContext<typename Black::EnumFlags<TEnumeration>::Bits>
	{
		// Underlying type.
		using UnderlyingType	= typename Black::EnumFlags<TEnumeration>::Bits;

		// JNI context for underlying type.
		using UnderlyingContext	= NativeContext<UnderlyingType>;


		// C++ native type.
		using NativeType	= Black::EnumFlags<TEnumeration>;

		// JNI type
		using JniType		= typename UnderlyingContext::JniType;


		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination )
		{
			UnderlyingType buffer;
			UnderlyingContext::FromJni( source, buffer );
			destination = Black::EnumFlags<TEnumeration>{ buffer };
		}

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination )
		{
			const UnderlyingType buffer{ source };
			UnderlyingContext::FromJni( buffer, destination );
		}
	};
}
}
}
}
