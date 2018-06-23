#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Internal
{
	inline void NativeContext<bool>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source == JNI_TRUE;
	}

	inline void NativeContext<char16_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<int8_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<int16_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<int32_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<int64_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<uint8_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<uint16_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<uint32_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<uint64_t>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<float>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<double>::FromJni( const JniType& source, NativeType& destination )
	{
		destination = source;
	}

	inline void NativeContext<std::string>::FromJni( const JniType& source, NativeType& destination )
	{
		destination.clear();
		CRET( source == nullptr );

		JNIEnv* local_env			= Black::JniConnection::GetLocalEnvironment();
		const jsize string_length	= local_env->GetStringUTFLength( source );
		CRET( string_length == 0 );

		destination.resize( static_cast<size_t>( string_length ), ' ' );
		local_env->GetStringUTFRegion( source, 0, string_length, &destination.front() );
	}

	inline void NativeContext<std::u16string>::FromJni( const JniType& source, NativeType& destination )
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
	inline void NativeContext<std::vector<TNativeValue, TAllocator>>::FromJni( const JniType& source, NativeType& destination )
	{
		destination.clear();
		CRET( source == nullptr );

		using ElementContext	= NativeContext<TNativeValue>;
		using JniArray			= typename ElementContext::ArrayType;
		using ArrayTrnslation	= Black::JniArrayTranslation<ElementContext>;

		ArrayTrnslation::FromJni( static_cast<JniArray>( source ), destination );
	}
}
}
}
}
