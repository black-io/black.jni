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
	inline void CommonTypeJniConverter<bool>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source == JNI_TRUE;
	}

	inline void CommonTypeJniConverter<char16_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<int8_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<int16_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<int32_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<int64_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<uint8_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<uint16_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<uint32_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<uint64_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<float>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<double>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<std::string>::FromJni( const JniType& source, NativeType& destination )
	{
		destination.clear();
		CRET( source == nullptr );

		JNIEnv* local_env					= Black::JniConnection::GetLocalEnvironment();
		const jsize string_multibyte_length	= local_env->GetStringUTFLength( source );
		const jsize string_unicode_length	= local_env->GetStringLength( source );
		CRET( string_multibyte_length == 0 );

		destination.resize( static_cast<size_t>( string_multibyte_length ), ' ' );
		local_env->GetStringUTFRegion( source, 0, string_unicode_length, destination.data() );
	}

	inline void CommonTypeJniConverter<std::u16string>::FromJni( const JniType& source, NativeType& destination )
	{
		destination.clear();
		CRET( source == nullptr );

		JNIEnv* local_env			= Black::JniConnection::GetLocalEnvironment();
		const jsize string_length	= local_env->GetStringLength( source );
		CRET( string_length == 0 );

		destination.resize( static_cast<size_t>( string_length ), ' ' );
		local_env->GetStringRegion( source, 0, string_length, reinterpret_cast<jchar*>( destination.data() ) );
	}

	template< typename TNativeValue, typename TAllocator >
	inline void CommonTypeJniConverter<std::vector<TNativeValue, TAllocator>>::FromJni( const JniType& source, NativeType& destination )
	{
		destination.clear();
		CRET( source == nullptr );

		using ElementConverter	= Black::JniNativeTypeConverter<TNativeValue>;
		using JniArray			= typename ElementConverter::ArrayType;
		using ArrayConverter	= Black::JniArrayConverter<ElementConverter>;

		ArrayConverter::FromJni( reinterpret_cast<const JniArray&>( source ), destination );
	}
}
}
}
}
}
