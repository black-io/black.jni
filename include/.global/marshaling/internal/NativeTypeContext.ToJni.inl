#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Internal
{
	inline void NativeContext<bool>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = ( source )? JNI_TRUE : JNI_FALSE;
	}

	inline void NativeContext<char16_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<int8_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<int16_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<int32_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<int64_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<uint8_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<uint16_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<uint32_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<uint64_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<float>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<double>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void NativeContext<const char*>::ToJni( const NativeType& source, JniType& destination )
	{
		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		destination			= local_env->NewStringUTF( source );
	}

	inline void NativeContext<const char16_t*>::ToJni( const NativeType& source, JniType& destination )
	{
		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		destination			= local_env->NewString( reinterpret_cast<const jchar*>( source ), std::char_traits<char16_t>::length( source ) );
	}

	inline void NativeContext<std::string>::ToJni( const NativeType& source, JniType& destination )
	{
		NativeContext<const char*>::ToJni( source.data(), destination );
	}

	inline void NativeContext<std::u16string>::ToJni( const NativeType& source, JniType& destination )
	{
		NativeContext<const char16_t*>::ToJni( source.data(), destination );
	}

	template< typename TNativeValue, typename TAllocator >
	inline void NativeContext<std::vector<TNativeValue, TAllocator>>::ToJni( const NativeType& source, JniType& destination )
	{
		using ElementContext	= NativeContext<TNativeValue>;
		using JniArray			= typename ElementContext::ArrayType;
		using ArrayTrnslation	= Black::JniArrayTranslation<ElementContext>;

		ArrayTrnslation::ToJni( source, reinterpret_cast<JniArray&>( destination ) );
	}
}
}
}
}
