#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	template< typename TElementContext, bool IS_TYPE_PLAIN >
	template< typename TAllocator >
	inline void JniArrayTranslation<TElementContext, IS_TYPE_PLAIN>::FromJni( const JniArray& source, NativeArray<TAllocator>& destination )
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

	template< typename TElementContext >
	template< typename TAllocator >
	inline void JniArrayTranslation<TElementContext, true>::FromJni( const JniArray& source, NativeArray<TAllocator>& destination )
	{
		JNIEnv* local_env			= Black::JniConnection::GetLocalEnvironment();
		const jsize array_length	= local_env->GetArrayLength( source );
		EXPECTS_DEBUG( destination.empty() );
		CRET( array_length == 0 );

		destination.reserve( static_cast<size_t>( array_length ) );

		constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= TElementContext::ARRAY_ELEMENTS_ACQUIRE_HANDLER;
		constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= TElementContext::ARRAY_ELEMENTS_RELEASE_HANDLER;

		auto array_data = (local_env->*ARRAY_ELEMENTS_ACQUIRE_HANDLER)( source, nullptr );

		std::transform(
			array_data, array_data + array_length, std::back_inserter( destination ),
			[]( const JniValue& data ) -> NativeValue
			{
				return Black::FromJni<NativeValue>( data );
			}
		);

		(local_env->*ARRAY_ELEMENTS_RELEASE_HANDLER)( source, array_data, JNI_ABORT );
	}
}
}
}
}
