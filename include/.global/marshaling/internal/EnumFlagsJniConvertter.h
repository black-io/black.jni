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
	// JNI environment context for `Black::EnumFlags` type.
	template< typename TEnumeration, typename TProjection >
	struct EnumFlagsJniConvertter final : CommonTypeContext<typename Black::EnumFlags<TEnumeration, TProjection>::Bits>
	{
		// Underlying type.
		using UnderlyingType	= typename Black::EnumFlags<TEnumeration, TProjection>::Bits;

		// JNI context for underlying type.
		using UnderlyingContext	= CommonTypeContext<UnderlyingType>;


		// C++ native type.
		using NativeType	= Black::EnumFlags<TEnumeration, TProjection>;

		// JNI type
		using JniType		= typename UnderlyingContext::JniType;


		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination )
		{
			UnderlyingType transition_buffer{};
			UnderlyingContext::FromJni( source, transition_buffer );
			destination = NativeType{ transition_buffer };
		}

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination )
		{
			const UnderlyingType transition_buffer{ source };
			UnderlyingContext::FromJni( transition_buffer, destination );
		}
	};
}
}
}
}
}
