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
	template< typename TElementContext, bool IS_ELEMENT_PLAIN >
	template< typename TAllocator >
	inline void ArrayTypeTranslation<TElementContext, IS_ELEMENT_PLAIN>::FromJni( const JniArray& source, NativeArray<TAllocator>& destination )
	{
		JNIEnv* local_env			= Black::JniConnection::GetLocalEnvironment();
		const jsize array_length	= local_env->GetArrayLength( source );
		EXPECTS_DEBUG( destination.empty() );
		CRET( array_length == 0 );

		destination.reserve( static_cast<size_t>( array_length ) );
		EXPECTS( local_env->PushLocalFrame( TElementContext::LOCAL_FRAME_SIZE * array_length ) == JNI_OK );

		constexpr auto ARRAY_ELEMENT_READ_HANDLER = TElementContext::ARRAY_ELEMENT_READ_HANDLER;
		for( jsize index = 0; index < array_length; ++index )
		{
			auto source_element = static_cast<JniValue>( (local_env->*ARRAY_ELEMENT_READ_HANDLER)( source, index ) );
			destination.emplace_back( Black::FromJni<NativeValue>( source_element ) );
		}

		local_env->PopLocalFrame( nullptr );
	}

	template< typename TElementContext, bool IS_ELEMENT_PLAIN >
	template< typename TAllocator >
	inline void ArrayTypeTranslation<TElementContext, IS_ELEMENT_PLAIN>::ToJni( const NativeArray<TAllocator>& source, JniArray& destination )
	{
		using ElementSignature = typename TElementContext::Signature;

		JNIEnv* local_env		= Black::JniConnection::GetLocalEnvironment();
		jclass element_class	= Black::JniConnection::GetClassReference( Black::JniClassPathString<ElementSignature>::GetData() );

		constexpr auto ARRAY_CONSTRUCT_HANDLER		= TElementContext::ARRAY_CONSTRUCT_HANDLER;
		constexpr auto ARRAY_ELEMENT_WRITE_HANDLER	= TElementContext::ARRAY_ELEMENT_WRITE_HANDLER;

		destination = (local_env->*ARRAY_CONSTRUCT_HANDLER)( static_cast<jsize>( source.size() ), element_class, nullptr );
		CRET( source.empty() );

		EXPECTS( local_env->PushLocalFrame( TElementContext::LOCAL_FRAME_SIZE * source.size() ) == JNI_OK );

		jsize index = 0;
		for( const auto& source_element : source )
		{
			(local_env->*ARRAY_ELEMENT_WRITE_HANDLER)( destination, index++, Black::ToJni( source_element ) );
		}

		local_env->PopLocalFrame( nullptr );
	}

	template< typename TElementContext >
	template< typename TAllocator >
	inline void ArrayTypeTranslation<TElementContext, true>::FromJni( const JniArray& source, NativeArray<TAllocator>& destination )
	{
		JNIEnv* local_env			= Black::JniConnection::GetLocalEnvironment();
		const jsize array_length	= local_env->GetArrayLength( source );
		EXPECTS_DEBUG( destination.empty() );
		CRET( array_length == 0 );

		destination.reserve( static_cast<size_t>( array_length ) );

		constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= TElementContext::ARRAY_ELEMENTS_ACQUIRE_HANDLER;
		constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= TElementContext::ARRAY_ELEMENTS_RELEASE_HANDLER;

		auto array_data = (local_env->*ARRAY_ELEMENTS_ACQUIRE_HANDLER)( source, nullptr );

		std::transform( array_data, array_data + array_length, std::back_inserter( destination ), Black::FromJni<NativeValue> );

		(local_env->*ARRAY_ELEMENTS_RELEASE_HANDLER)( source, array_data, JNI_ABORT );
	}

	template< typename TElementContext >
	template< typename TAllocator >
	inline void ArrayTypeTranslation<TElementContext, true>::ToJni( const NativeArray<TAllocator>& source, JniArray& destination )
	{
		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();

		constexpr auto ARRAY_CONSTRUCT_HANDLER			= TElementContext::ARRAY_CONSTRUCT_HANDLER;
		constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= TElementContext::ARRAY_ELEMENTS_ACQUIRE_HANDLER;
		constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= TElementContext::ARRAY_ELEMENTS_RELEASE_HANDLER;

		destination = (local_env->*ARRAY_CONSTRUCT_HANDLER)( static_cast<jsize>( source.size() ) );
		CRET( source.empty() );

		auto destination_data = (local_env->*ARRAY_ELEMENTS_ACQUIRE_HANDLER)( destination, nullptr );

		std::transform( source.begin(), source.end(), destination_data, Black::ToJni<NativeValue> );

		(local_env->*ARRAY_ELEMENTS_RELEASE_HANDLER)( destination, destination_data, JNI_OK );
	}
}
}
}
}
}
