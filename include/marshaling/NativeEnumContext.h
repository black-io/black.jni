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
	struct EnumContext<TNativeEnum, true> : NativeContext<Black::UnderlyingType<TNativeEnum>>
	{
		// Underlying type for enumeration type.
		using UnderlyingType	= Black::UnderlyingType<TNativeEnum>;

		// JNI context for underlying type.
		using UnderlyingContext	= NativeContext<UnderlyingType>;


		// C++ native type.
		using NativeType	= TNativeEnum;

		// JNI type
		using JniType		= typename UnderlyingContext::JniType;


		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination )
		{
			UnderlyingType buffer;
			UnderlyingContext::FromJni( source, buffer );
			destination = static_cast<TNativeEnum>( buffer );
		}

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination )
		{
			const UnderlyingType buffer = static_cast<UnderlyingType>( source );
			UnderlyingContext::FromJni( buffer, destination );
		}
	};
}


	// JNI environment context for native enumerations.
	template< typename TNativeEnum >
	using NativeEnumContext = Traits::EnumContext<TNativeEnum, Black::IS_ENUMERATION<TNativeEnum>>;
}
}
}
