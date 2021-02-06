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
	inline void CommonTypeContext<bool>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source == JNI_TRUE;
	}

	inline void CommonTypeContext<char16_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<int8_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<int16_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<int32_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<int64_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<uint8_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<uint16_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<uint32_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<uint64_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<float>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<double>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<std::string>::FromJni( const JniType& source, NativeType& destination )
	{
		destination.clear();
		CRET( source == nullptr );

		JNIEnv* local_env			= Black::JniConnection::GetLocalEnvironment();
		const jsize string_length	= local_env->GetStringUTFLength( source );
		CRET( string_length == 0 );

		destination.resize( static_cast<size_t>( string_length ), ' ' );
		local_env->GetStringUTFRegion( source, 0, string_length, &destination.front() );
	}

	inline void CommonTypeContext<std::u16string>::FromJni( const JniType& source, NativeType& destination )
	{
		destination.clear();
		CRET( source == nullptr );

		JNIEnv* local_env			= Black::JniConnection::GetLocalEnvironment();
		const jsize string_length	= local_env->GetStringLength( source );
		CRET( string_length == 0 );

		destination.resize( static_cast<size_t>( string_length ), ' ' );
		local_env->GetStringRegion( source, 0, string_length, reinterpret_cast<jchar*>( &destination.front() ) );
	}

	template< typename TNativeValue, typename TAllocator >
	inline void CommonTypeContext<std::vector<TNativeValue, TAllocator>>::FromJni( const JniType& source, NativeType& destination )
	{
		destination.clear();
		CRET( source == nullptr );

		using ElementContext	= CommonTypeContext<TNativeValue>;
		using JniArray			= typename ElementContext::ArrayType;
		using ArrayTrnslation	= Black::JniArrayTranslation<ElementContext>;

		ArrayTrnslation::FromJni( static_cast<JniArray>( source ), destination );
	}
}
}
}
}
}
