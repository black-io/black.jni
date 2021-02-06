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
	inline void CommonTypeContext<bool>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = ( source )? JNI_TRUE : JNI_FALSE;
	}

	inline void CommonTypeContext<char16_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<int8_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<int16_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<int32_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<int64_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<uint8_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<uint16_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<uint32_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<uint64_t>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<float>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<double>::ToJni( const NativeType& source, JniType& destination )
	{
		destination = source;
	}

	inline void CommonTypeContext<const char*>::ToJni( const NativeType& source, JniType& destination )
	{
		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		destination			= local_env->NewStringUTF( source );
	}

	inline void CommonTypeContext<const char16_t*>::ToJni( const NativeType& source, JniType& destination )
	{
		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		destination			= local_env->NewString( reinterpret_cast<const jchar*>( source ), std::char_traits<char16_t>::length( source ) );
	}

	inline void CommonTypeContext<std::string_view>::ToJni( const NativeType& source, JniType& destination )
	{
		char* const transition_buffer = static_cast<char*>( alloca( source.length() + 1 ) );
		Black::CopyMemory( transition_buffer, source.data(), source.length() );
		transition_buffer[ source.length() ] = 0;
		CommonTypeContext<const char*>::ToJni( transition_buffer, destination );
	}

	inline void CommonTypeContext<std::u16string_view>::ToJni( const NativeType& source, JniType& destination )
	{
		constexpr size_t element_size = sizeof( char16_t );
		const size_t source_size = source.length() * element_size;

		char16_t* const transition_buffer = static_cast<char16_t*>( alloca( source_size + element_size ) );
		Black::CopyMemory( transition_buffer, source.data(), source_size );
		transition_buffer[ source.length() ] = 0;
		CommonTypeContext<const char16_t*>::ToJni( transition_buffer, destination );
	}

	inline void CommonTypeContext<std::string>::ToJni( const NativeType& source, JniType& destination )
	{
		CommonTypeContext<const char*>::ToJni( source.data(), destination );
	}

	inline void CommonTypeContext<std::u16string>::ToJni( const NativeType& source, JniType& destination )
	{
		CommonTypeContext<const char16_t*>::ToJni( source.data(), destination );
	}

	template< typename TNativeValue, typename TAllocator >
	inline void CommonTypeContext<std::vector<TNativeValue, TAllocator>>::ToJni( const NativeType& source, JniType& destination )
	{
		using ElementContext	= CommonTypeContext<TNativeValue>;
		using JniArray			= typename ElementContext::ArrayType;
		using ArrayTrnslation	= Black::JniArrayTranslation<ElementContext>;

		ArrayTrnslation::ToJni( source, static_cast<JniArray&>( destination ) );
	}
}
}
}
}
}
