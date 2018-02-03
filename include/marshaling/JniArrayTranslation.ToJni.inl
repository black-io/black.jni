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
	inline void JniArrayTranslation<TElementContext, IS_TYPE_PLAIN>::ToJni( const NativeArray<TAllocator>& source, JniArray& destination )
	{
		using ElementSignature = typename TElementContext::Signature;

		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();
		const Black::JniClass element_class{ Black::JniClassPath<ElementSignature>::GetData() };

		constexpr auto ARRAY_CONSTRUCT_HANDLER		= TElementContext::ARRAY_CONSTRUCT_HANDLER;
		constexpr auto ARRAY_ELEMENT_WRITE_HANDLER	= TElementContext::ARRAY_ELEMENT_WRITE_HANDLER;

		destination = (local_env->*ARRAY_CONSTRUCT_HANDLER)( static_cast<jsize>( source.size() ), *element_class, nullptr );
		CRET( source.empty() );

		EXPECTS( local_env->PushLocalFrame( TElementContext::LOCAL_FRAME_SIZE * array_length ) == JNI_OK );

		jsize index = 0;
		for( const auto& source_element : source )
		{
			(local_env->*ARRAY_ELEMENT_WRITE_HANDLER)( destination, index++, Black::ToJni( source_element ) );
		}

		local_env->PopLocalFrame( nullptr );
	}

	template< typename TElementContext >
	template< typename TAllocator >
	inline void JniArrayTranslation<TElementContext, true>::ToJni( const NativeArray<TAllocator>& source, JniArray& destination )
	{

	}
}
}
}
}
