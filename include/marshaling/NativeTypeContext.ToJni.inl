#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	inline void NativeContext<bool>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<char16_t>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<int8_t>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<int16_t>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<int32_t>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<int64_t>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<uint8_t>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<uint16_t>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<uint32_t>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<uint64_t>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<float>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<double>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<const char*>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<const char16_t*>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<std::string>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	inline void NativeContext<std::u16string>::ToJni( const NativeType& source, JniType& destination )
	{

	}

	template< typename TNativeValue, typename TAllocator >
	inline void NativeContext<std::vector<TNativeValue, TAllocator>>::ToJni( const NativeType& source, JniType& destination )
	{

	}
}
}
}
}
