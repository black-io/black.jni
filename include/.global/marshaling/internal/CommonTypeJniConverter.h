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
		@brief	Type translation environment for particular C++ type.

		This context used to properly translate known native C++ type into JNI-consumed type and back from JNI-consumed type.

		@tparam	TNativeType	Native C++ type, for which the translation is required.
	*/
	template< typename TNativeType >
	struct CommonTypeJniConverter;

	// Type translation environment for `void` type.
	template<>
	struct CommonTypeJniConverter<void> : CommonTypeJniContext<void>, CommonTypeSignature<void>
	{
		// Count of local references required to store this type in Dalvik local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= void;

		// JNI type
		using JniType		= void;
	};

	// Type translation environment for `bool` type.
	template<>
	struct CommonTypeJniConverter<bool> : CommonTypeJniContext<jboolean>, CommonTypeSignature<jboolean>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= bool;

		// JNI type
		using JniType		= jboolean;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `char16_t` type.
	template<>
	struct CommonTypeJniConverter<char16_t> : CommonTypeJniContext<jchar>, CommonTypeSignature<jchar>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= char16_t;

		// JNI type
		using JniType		= jchar;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `int8_t` type.
	template<>
	struct CommonTypeJniConverter<int8_t> : CommonTypeJniContext<jbyte>, CommonTypeSignature<jbyte>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= int8_t;

		// JNI type
		using JniType		= jbyte;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `int16_t` type.
	template<>
	struct CommonTypeJniConverter<int16_t> : CommonTypeJniContext<jshort>, CommonTypeSignature<jshort>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= int16_t;

		// JNI type
		using JniType		= jshort;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `int32_t` type.
	template<>
	struct CommonTypeJniConverter<int32_t> : CommonTypeJniContext<jint>, CommonTypeSignature<jint>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= int32_t;

		// JNI type
		using JniType		= jint;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `int64_t` type.
	template<>
	struct CommonTypeJniConverter<int64_t> : CommonTypeJniContext<jlong>, CommonTypeSignature<jlong>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= int64_t;

		// JNI type
		using JniType		= jlong;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `uint8_t` type.
	template<>
	struct CommonTypeJniConverter<uint8_t> : CommonTypeJniContext<jshort>, CommonTypeSignature<jshort>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= uint8_t;

		// JNI type
		using JniType		= jshort;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `uint16_t` type.
	template<>
	struct CommonTypeJniConverter<uint16_t> : CommonTypeJniContext<jint>, CommonTypeSignature<jint>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= uint16_t;

		// JNI type
		using JniType		= jint;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `uint32_t` type.
	template<>
	struct CommonTypeJniConverter<uint32_t> : CommonTypeJniContext<jlong>, CommonTypeSignature<jlong>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= uint32_t;

		// JNI type
		using JniType		= jlong;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `uint64_t` type.
	template<>
	struct CommonTypeJniConverter<uint64_t> : CommonTypeJniContext<jlong>, CommonTypeSignature<jlong>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= uint64_t;

		// JNI type
		using JniType		= jlong;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `float` type.
	template<>
	struct CommonTypeJniConverter<float> : CommonTypeJniContext<jfloat>, CommonTypeSignature<jfloat>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= float;

		// JNI type
		using JniType		= jfloat;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `double` type.
	template<>
	struct CommonTypeJniConverter<double> : CommonTypeJniContext<jdouble>, CommonTypeSignature<jdouble>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 0;

		// C++ native type.
		using NativeType	= double;

		// JNI type
		using JniType		= jdouble;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `const char*` type.
	template<>
	struct CommonTypeJniConverter<const char*> : CommonTypeJniContext<jobject>, CommonTypeSignature<jstring>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 1;

		// C++ native type.
		using NativeType	= const char*;

		// JNI type
		using JniType		= jstring;

		// Type translation from JNI space to C++ space.
		//static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `const char16_t*` type.
	template<>
	struct CommonTypeJniConverter<const char16_t*> : CommonTypeJniContext<jobject>, CommonTypeSignature<jstring>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 1;

		// C++ native type.
		using NativeType	= const char16_t*;

		// JNI type
		using JniType		= jstring;

		// Type translation from JNI space to C++ space.
		//static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `std::string_view` type.
	template<>
	struct CommonTypeJniConverter<std::string_view> : CommonTypeJniContext<jobject>, CommonTypeSignature<jstring>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 1;

		// C++ native type.
		using NativeType	= std::string_view;

		// JNI type
		using JniType		= jstring;

		// Type translation from JNI space to C++ space.
		//static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `std::u16string_view` type.
	template<>
	struct CommonTypeJniConverter<std::u16string_view> : CommonTypeJniContext<jobject>, CommonTypeSignature<jstring>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 1;

		// C++ native type.
		using NativeType	= std::u16string_view;

		// JNI type
		using JniType		= jstring;

		// Type translation from JNI space to C++ space.
		//static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `std::string` type.
	template<>
	struct CommonTypeJniConverter<std::string> : CommonTypeJniContext<jobject>, CommonTypeSignature<jstring>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 1;

		// C++ native type.
		using NativeType	= std::string;

		// JNI type
		using JniType		= jstring;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `std::u16string` type.
	template<>
	struct CommonTypeJniConverter<std::u16string> : CommonTypeJniContext<jobject>, CommonTypeSignature<jstring>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 1;

		// C++ native type.
		using NativeType	= std::u16string;

		// JNI type
		using JniType		= jstring;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination );

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination );
	};

	// Type translation environment for `std::vector` type.
	template< typename TNativeValue, typename TAllocator >
	struct CommonTypeJniConverter<std::vector<TNativeValue, TAllocator>> : CommonTypeJniContext<jobject>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t LOCAL_FRAME_SIZE = 1;

		// JNI type signature.
		using Signature		= Black::JniArraySignatureString<typename CommonTypeJniConverter<TNativeValue>::Signature>;

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
}
}
}
}
