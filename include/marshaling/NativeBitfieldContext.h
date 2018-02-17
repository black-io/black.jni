#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	// Safe environment context for native bit-fields.
	template< typename TNativeBitfield, bool IS_VALID_BITFIELD >
	struct BitfieldContext;

	// JNI environment context for native bit-fields.
	template< typename TNativeBitfield >
	struct BitfieldContext<TNativeBitfield, true> : NativeContext<decltype( std::declval<TNativeBitfield>().bits )>
	{
		// Underlying type for bit-field type.
		using UnderlyingType	= decltype( std::declval<TNativeBitfield>().bits );

		// JNI context for underlying type.
		using UnderlyingContext	= NativeContext<UnderlyingType>;


		// C++ native type.
		using NativeType	= TNativeBitfield;

		// JNI type
		using JniType		= typename UnderlyingContext::JniType;


		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination )
		{
			UnderlyingContext::FromJni( source, destination.bits );
		}

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination )
		{
			UnderlyingContext::FromJni( source.bits, destination );
		}
	};
}


	// JNI environment context for native bit-fields.
	template< typename TNativeBitfield >
	using NativeBitfieldContext = Traits::BitfieldContext<TNativeBitfield, Black::IS_BIT_FIELD<TNativeBitfield>>;
}
}
}
