#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	// JNI environment context for regular native type.
	template< typename TNativeType >
	struct NativeContext;

	// JNI environment context for `void` type.
	template<>
	struct NativeContext<void> : JniContext<void>, JniSignature<void>
	{
		// Count of local references required to store this type in Dalvik local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= void;

		// JNI type
		using JniType		= void;

		// Type translation from JNI space to C++ space.
		//static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		//static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `bool` type.
	template<>
	struct NativeContext<bool> : JniContext<jboolean>, JniSignature<jboolean>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= bool;

		// JNI type
		using JniType		= jboolean;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `char16_t` type.
	template<>
	struct NativeContext<char16_t> : JniContext<jchar>, JniSignature<jchar>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= char16_t;

		// JNI type
		using JniType		= jchar;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `int8_t` type.
	template<>
	struct NativeContext<int8_t> : JniContext<jbyte>, JniSignature<jbyte>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= int8_t;

		// JNI type
		using JniType		= jbyte;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `int16_t` type.
	template<>
	struct NativeContext<int16_t> : JniContext<jshort>, JniSignature<jshort>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= int16_t;

		// JNI type
		using JniType		= jshort;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `int32_t` type.
	template<>
	struct NativeContext<int32_t> : JniContext<jint>, JniSignature<jint>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= int32_t;

		// JNI type
		using JniType		= jint;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `int64_t` type.
	template<>
	struct NativeContext<int64_t> : JniContext<jlong>, JniSignature<jlong>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= int64_t;

		// JNI type
		using JniType		= jlong;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `uint8_t` type.
	template<>
	struct NativeContext<uint8_t> : JniContext<jshort>, JniSignature<jshort>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= uint8_t;

		// JNI type
		using JniType		= jshort;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `uint16_t` type.
	template<>
	struct NativeContext<uint16_t> : JniContext<jint>, JniSignature<jint>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= uint16_t;

		// JNI type
		using JniType		= jint;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `uint32_t` type.
	template<>
	struct NativeContext<uint32_t> : JniContext<jlong>, JniSignature<jlong>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= uint32_t;

		// JNI type
		using JniType		= jlong;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `uint64_t` type.
	template<>
	struct NativeContext<uint64_t> : JniContext<jlong>, JniSignature<jlong>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= uint64_t;

		// JNI type
		using JniType		= jlong;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `float` type.
	template<>
	struct NativeContext<float> : JniContext<jfloat>, JniSignature<jfloat>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= float;

		// JNI type
		using JniType		= jfloat;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `double` type.
	template<>
	struct NativeContext<double> : JniContext<jdouble>, JniSignature<jdouble>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= double;

		// JNI type
		using JniType		= jdouble;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `const char*` type.
	template<>
	struct NativeContext<const char*> : JniContext<jobject>, JniSignature<jstring>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		// C++ native type.
		using NativeType	= const char*;

		// JNI type
		using JniType		= jstring;

		// Type translation from JNI space to C++ space.
		//static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `const char16_t*` type.
	template<>
	struct NativeContext<const char16_t*> : JniContext<jobject>, JniSignature<jstring>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		// C++ native type.
		using NativeType	= const char16_t*;

		// JNI type
		using JniType		= jstring;

		// Type translation from JNI space to C++ space.
		//static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `std::string` type.
	template<>
	struct NativeContext<std::string> : JniContext<jobject>, JniSignature<jstring>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		// C++ native type.
		using NativeType	= std::string;

		// JNI type
		using JniType		= jstring;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `std::u16string` type.
	template<>
	struct NativeContext<std::u16string> : JniContext<jobject>, JniSignature<jstring>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		// C++ native type.
		using NativeType	= std::u16string;

		// JNI type
		using JniType		= jstring;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// JNI environment context for `std::vector` type.
	template< typename TNativeValue, typename TAllocator >
	struct NativeContext< std::vector<TNativeValue, TAllocator> > : JniContext<jobject>
	{
		// Count of local references required to store this type in JNI local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		// JNI type signature.
		using Signature		= Black::JniArraySignature<typename NativeContext<TNativeValue>::Signature>;

		// C++ native type.
		using NativeType	= std::vector<TNativeValue, TAllocator>;

		// JNI type
		using JniType		= jarray;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};
}


	// JNI environment context for regular native type.
	template< typename TNativeType >
	using NativeTypeContext		= Traits::NativeContext<TNativeType>;

	// JNI representation for regular native type.
	template< typename TNativeType >
	using JniType				= typename Traits::NativeContext<TNativeType>::JniType;

	// JNI type signature for regular native type.
	template< typename TNativeType >
	using NativeTypeSignature	= typename Traits::NativeContext<TNativeType>::Signature;

	/**
		@brief	Regular converting function from Jni type to C++ one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, JNI-side.
		@param	destination	Final storage of converted value, C++-side.
	*/
	template< typename TNativeType >
	inline void FromJni( const JniType<TNativeType>& source, TNativeType& destination )
	{
		NativeTypeTraits<TNativeType>::FromJni( source, destination );
	}

	/**
		@brief	Regular converting function from C++ type to Jni one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, C++-side.
		@param	destination	Final storage of converted value, Jni-side.
	*/
	template< typename TNativeType >
	inline void ToJni( const TNativeType& source, JniType<TNativeType>& destination )
	{
		NativeTypeTraits<TNativeType>::ToJni( source, destination );
	}

	/**
		@brief	NRVO-optimizable converting function from Jni type to C++ one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, Jni-side.
		@return				Final storage of converted value, C++-side.
	*/
	template< typename TNativeType >
	inline TNativeType FromJni( const JniType<TNativeType>& source )
	{
		TNativeType destination;
		NativeTypeTraits<TNativeType>::FromJni( source, destination );
		return destination;
	}

	/**
		@brief	NRVO-optimizable converting function from C++ type to Java one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, C++-side.
		@return				Final storage of converted value, Java-side.
	*/
	template< typename TNativeType >
	inline JniType<TNativeType> ToJni( const TNativeType& source )
	{
		JniType<TNativeType> destination;
		NativeTypeTraits<TNativeType>::ToJni( source, destination );
		return destination;
	}
}
}
}
