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
	/**
		@brief	Array type converter.

		This converter is only wrap for converters of any particular array types. It only implements the valid routine for elements marshaling.
		The type of native-side array is `std::vector`, it perfectly fits the requirements of Java array to operate on elements.

		@tparam	TElementConverter	Type of JNI converter for array elements.
		@tparam	IS_ELEMENT_PLAIN	Whether the array elements are plain Java types or not.
	*/
	template< typename TElementConverter, bool IS_ELEMENT_PLAIN >
	struct ArrayTypeConverter final
	{
		// JNI regular type of single element.
		using JniValue		= typename TElementConverter::JniType;

		// JNI regular type of array.
		using JniArray		= typename TElementConverter::ArrayType;

		// Native regular type of single element.
		using NativeValue	= typename TElementConverter::NativeType;

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

	// Array converter for plain Java elements, it uses Java memory locking to access the elements.
	template< typename TElementConverter >
	struct ArrayTypeConverter<TElementConverter, true> final
	{
		// JNI regular type of single element.
		using JniValue		= typename TElementConverter::JniType;

		// JNI regular type of array.
		using JniArray		= typename TElementConverter::ArrayType;

		// Native regular type of single element.
		using NativeValue	= typename TElementConverter::NativeType;

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
}
}
}
}
