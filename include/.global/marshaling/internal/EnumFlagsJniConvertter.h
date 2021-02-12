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
		@brief	JNI converter for `Black::EnumFlags` instantiations.

		This converter will be used by default for any instantiation of `Black::EnumFlags` template.

		@tparam	TEnumeration	Enumeration type used as flags collection.
		@tparam	TProjection		Projection type for enumeration flags.
	*/
	template< typename TEnumeration, typename TProjection >
	struct EnumFlagsJniConvertter final : CommonTypeJniConverter<typename Black::EnumFlags<TEnumeration, TProjection>::Bits>
	{
		// Underlying type.
		using UnderlyingType		= typename Black::EnumFlags<TEnumeration, TProjection>::Bits;

		// JNI context for underlying type.
		using UnderlyingConvrter	= CommonTypeJniConverter<UnderlyingType>;


		// C++ native type.
		using NativeType	= Black::EnumFlags<TEnumeration, TProjection>;

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
			const UnderlyingType transition_buffer{ source };
			UnderlyingConvrter::FromJni( transition_buffer, destination );
		}
	};
}
}
}
}
}
