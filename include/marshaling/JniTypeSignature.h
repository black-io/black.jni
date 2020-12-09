#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Internal
{
	// JNI regular type signature specification.
	template< typename TJniType >
	struct JniSignature;

	// `void` type signature.
	template<>
	struct JniSignature<void>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'V'>;
	};

	// `boolean` type signature.
	template<>
	struct JniSignature<jboolean>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'Z'>;
	};

	// `byte` type signature.
	template<>
	struct JniSignature<jbyte>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'B'>;
	};

	// `char` type signature.
	template<>
	struct JniSignature<jchar>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'C'>;
	};

	// `short` type signature.
	template<>
	struct JniSignature<jshort>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'S'>;
	};

	// `int` type signature.
	template<>
	struct JniSignature<jint>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'I'>;
	};

	// `long` type signature.
	template<>
	struct JniSignature<jlong>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'J'>;
	};

	// `float` type signature.
	template<>
	struct JniSignature<jfloat>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'F'>;
	};

	// `double` type signature.
	template<>
	struct JniSignature<jdouble>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'D'>;
	};

	// `java.lang.Object` type signature.
	template<>
	struct JniSignature<jobject>
	{
		// JNI signature.
		using Signature	= Black::JniClassSignatureString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'O', 'b', 'j', 'e', 'c', 't'>;
	};

	// `java.lang.Class` type signature.
	template<>
	struct JniSignature<jclass>
	{
		// JNI signature.
		using Signature	= Black::JniClassSignatureString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's'>;
	};

	// `java.lang.String` type signature.
	template<>
	struct JniSignature<jstring>
	{
		// JNI signature.
		using Signature	= Black::JniClassSignatureString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g'>;
	};
}


	// Type signature for any regular JNI type.
	template< typename TJniType >
	using JniTypeSignature		= typename Internal::JniSignature<TJniType>::Signature;

	// Function signature for any JNI type.
	template< typename TJniResult, typename... TJniArguments >
	using JniFunctionSignature	= Black::JniFunctionSignatureString<JniTypeSignature<TJniResult>, JniTypeSignature<TJniArguments>...>;
}
}
}
