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
	/**
		@brief	JNI converter for User-defined bit-fields.

		The user-defined bit-field should satisfy the requirements of convertible bit-fields.
		* The bit-field is the union.
		* There is member-field `bits` defined, that represents the buffer of all bits.

		@tparam	TNativeBitfield	Type of bit-field for conversion.
	*/
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
