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
		@brief	JNI converter for values of regular enumeration type.

		This converter will be used by default for any value of enumeration type.

		@tparam	TNativeEnum	Given enumeration type.
	*/
	template< typename TNativeEnum >
	struct EnumJniConverter : CommonTypeJniConverter<std::underlying_type_t<TNativeEnum>>
	{
		// Underlying type for enumeration type.
		using UnderlyingType		= std::underlying_type_t<TNativeEnum>;

		// JNI context for underlying type.
		using UnderlyingConvrter	= CommonTypeJniConverter<UnderlyingType>;


		// C++ native type.
		using NativeType	= TNativeEnum;

		// JNI type
		using JniType		= typename UnderlyingConvrter::JniType;


		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination )
		{
			UnderlyingType transition_buffer{};
			UnderlyingConvrter::FromJni( source, transition_buffer );
			destination = NativeType{ transition_buffer };
		}

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination )
		{
			const UnderlyingType transition_buffer = Black::GetEnumValue( source );
			UnderlyingConvrter::FromJni( transition_buffer, destination );
		}
	};
}
}
}
}
}
