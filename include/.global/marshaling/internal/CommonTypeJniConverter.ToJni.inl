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
	inline void CommonTypeJniConverter<bool>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = ( source )? JNI_TRUE : JNI_FALSE;
	}

	inline void CommonTypeJniConverter<char16_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<int8_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<int16_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<int32_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<int64_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<uint8_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<uint16_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<uint32_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<uint64_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<float>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<double>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeJniConverter<const char*>::ToJni( const NativeType& source, JniType& destination )
	{
		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		destination			= local_env->NewStringUTF( source );
	}

	inline void CommonTypeJniConverter<const char16_t*>::ToJni( const NativeType& source, JniType& destination )
	{
		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		destination			= local_env->NewString( reinterpret_cast<const jchar*>( source ), std::char_traits<char16_t>::length( source ) );
	}

	inline void CommonTypeJniConverter<std::string_view>::ToJni( const NativeType& source, JniType& destination )
	{
		char* const transition_buffer = static_cast<char*>( alloca( source.length() + 1 ) );
		Black::CopyMemory( transition_buffer, source.data(), source.length() );
		transition_buffer[ source.length() ] = 0;
		CommonTypeJniConverter<const char*>::ToJni( transition_buffer, destination );
	}

	inline void CommonTypeJniConverter<std::u16string_view>::ToJni( const NativeType& source, JniType& destination )
	{
		constexpr size_t element_size = sizeof( char16_t );
		const size_t source_size = source.length() * element_size;

		char16_t* const transition_buffer = static_cast<char16_t*>( alloca( source_size + element_size ) );
		Black::CopyMemory( transition_buffer, source.data(), source_size );
		transition_buffer[ source.length() ] = 0;
		CommonTypeJniConverter<const char16_t*>::ToJni( transition_buffer, destination );
	}

	inline void CommonTypeJniConverter<std::string>::ToJni( const NativeType& source, JniType& destination )
	{
		CommonTypeJniConverter<const char*>::ToJni( source.data(), destination );
	}

	inline void CommonTypeJniConverter<std::u16string>::ToJni( const NativeType& source, JniType& destination )
	{
		CommonTypeJniConverter<const char16_t*>::ToJni( source.data(), destination );
	}

	template< typename TNativeValue, typename TAllocator >
	inline void CommonTypeJniConverter<std::vector<TNativeValue, TAllocator>>::ToJni( const NativeType& source, JniType& destination )
	{
		using ElementConverter	= Black::JniNativeTypeConverter<TNativeValue>;
		using JniArray			= typename ElementConverter::ArrayType;
		using ArrayConverter	= Black::JniArrayConverter<ElementConverter>;

		ArrayConverter::ToJni( source, reinterpret_cast<JniArray&>( destination ) );
	}
}
}
}
}
}
