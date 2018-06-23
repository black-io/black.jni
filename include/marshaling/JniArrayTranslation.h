#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Internal
{
	// Translation traits for JNI object arrays.
	template< typename TElementContext, bool IS_TYPE_PLAIN >
	struct JniArrayTranslation
	{
		// JNI regular type of single element.
		using JniValue		= typename TElementContext::JniType;

		// JNI regular type of array.
		using JniArray		= typename TElementContext::ArrayType;

		// Native regular type of single element.
		using NativeValue	= typename TElementContext::NativeType;

		// Native regular type of array.
		template< typename TAllocator >
		using NativeArray	= std::vector<NativeValue, TAllocator>;


		// Transform the array from JNI regular type to native one.
		template< typename TAllocator >
		static inline void FromJni( const JniArray& source, NativeArray<TAllocator>& destination );

		// Transform the array from Native regular type to JNI one.
		template< typename TAllocator >
		static inline void ToJni( const NativeArray<TAllocator>& source, JniArray& destination );
	};

	// Translation traits for JNI plain arrays.
	template< typename TElementContext >
	struct JniArrayTranslation<TElementContext, true>
	{
		// JNI regular type of single element.
		using JniValue		= typename TElementContext::JniType;

		// JNI regular type of array.
		using JniArray		= typename TElementContext::ArrayType;

		// Native regular type of single element.
		using NativeValue	= typename TElementContext::NativeType;

		// Native regular type of array.
		template< typename TAllocator >
		using NativeArray	= std::vector<NativeValue, TAllocator>;


		// Transform the array from JNI regular type to native one.
		template< typename TAllocator >
		static inline void FromJni( const JniArray& source, NativeArray<TAllocator>& destination );

		// Transform the array from Native regular type to JNI one.
		template< typename TAllocator >
		static inline void ToJni( const NativeArray<TAllocator>& source, JniArray& destination );
	};
}


	// JNI array type translation.
	template< typename TElementContext >
	using JniArrayTranslation = Internal::JniArrayTranslation<TElementContext, TElementContext::IS_PLAIN>;
}
}
}
