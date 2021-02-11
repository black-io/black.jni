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
	struct BitfieldJniConverter : CommonTypeJniConverter<decltype( std::declval<TNativeBitfield>().bits )>
	{
		// Underlying type for bit-field type.
		using UnderlyingType		= decltype( std::declval<TNativeBitfield>().bits );

		// JNI context for underlying type.
		using UnderlyingConvrter	= CommonTypeJniConverter<UnderlyingType>;


		// C++ native type.
		using NativeType	= TNativeBitfield;

		// JNI type
		using JniType		= typename UnderlyingConvrter::JniType;


		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination )
		{
			UnderlyingConvrter::FromJni( source, destination.bits );
		}

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination )
		{
			UnderlyingConvrter::FromJni( source.bits, destination );
		}
	};
}
}
}
}
}
