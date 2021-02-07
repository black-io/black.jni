#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Global
{
inline namespace Marshaling
{
namespace Internal
{
	// Safe environment context for native bit-fields.
	template< typename TNativeBitfield >
	struct BitfieldContext : CommonTypeContext<decltype( std::declval<TNativeBitfield>().bits )>
	{
		// Underlying type for bit-field type.
		using UnderlyingType	= decltype( std::declval<TNativeBitfield>().bits );

		// JNI context for underlying type.
		using UnderlyingContext	= CommonTypeContext<UnderlyingType>;


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
}
}
}
}
