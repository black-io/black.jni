#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	// Safe environment context for native enumeration.
	template< typename TNativeEnum, bool IS_VALID_ENUMERATION >
	struct EnumContext;

	// JNI environment context for native enumeration.
	template< typename TNativeEnum >
	struct EnumContext<TNativeEnum, true> : Black::NativeTypeContext<Black::UnderlyingType<TNativeEnum>>
	{
		// Underlying type for enumeration type.
		using UnderlyingType	= typename std::underlying_type<TNativeEnum>::type;

		// Native type traits for underlying type of enumeration type.
		using UnderlyingContext	= Black::NativeTypeContext<UnderlyingType>;


		// C++ native type.
		using NativeType	= TNativeEnum;

		// JNI type
		using JniType		= typename UnderlyingContext::JniType;


		// Type translation from JNI space to C++ space.
		static inline void FromJava( const JniType& source, NativeType& destination )
		{
			UnderlyingType buffer;
			UnderlyingContext::FromJava( source, buffer );
			destination = static_cast<TNativeEnum>( buffer );
		}

		// Type translation from C++ space to JNI space.
		static inline void ToJava( const NativeType& source, JniType& destination )
		{
			const UnderlyingType buffer = static_cast<UnderlyingType>( source );
			UnderlyingContext::FromJava( buffer, destination );
		}
	};
}


	// JNI environment context for native enumerations.
	template< typename TNativeEnum >
	using NativeEnumContext = Traits::EnumContext<TNativeEnum, Black::IS_ENUMERATION<TNativeEnum>>;
}
}
}
