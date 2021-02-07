#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Global
{
inline namespace Marshaling
{
	template< typename TNativeType >
	inline void ConvertFromJni( const JniType<TNativeType>& source, TNativeType& destination )
	{
		JniNativeTypeConverter<TNativeType>::FromJni( source, destination );
	}

	template< typename TNativeType >
	inline void ConvertToJni( const TNativeType& source, JniType<TNativeType>& destination )
	{
		JniNativeTypeConverter<TNativeType>::ToJni( source, destination );
	}

	template< typename TNativeType >
	inline TNativeType ConvertFromJni( const JniType<TNativeType>& source )
	{
		TNativeType destination{};
		JniNativeTypeConverter<TNativeType>::FromJni( source, destination );
		return destination;
	}

	template< typename TNativeType >
	inline JniType<TNativeType> ConvertToJni( const TNativeType& source )
	{
		JniType<TNativeType> destination{};
		JniNativeTypeConverter<TNativeType>::ToJni( source, destination );
		return destination;
	}

	template< typename... TNativeTypes >
	inline constexpr size_t CalculateLocalFrameSize()
	{
		return (JniNativeTypeConverter<TNativeTypes>::LOCAL_FRAME_SIZE + ...);
	}
}
}
}
}
