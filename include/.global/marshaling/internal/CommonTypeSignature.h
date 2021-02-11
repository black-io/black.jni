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
	// Signature in JNI notation for common types.
	template< typename TJniType >
	struct CommonTypeSignature;

	// `void` type signature.
	template<>
	struct CommonTypeSignature<void>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'V'>;
	};

	// `boolean` type signature.
	template<>
	struct CommonTypeSignature<jboolean>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'Z'>;
	};

	// `byte` type signature.
	template<>
	struct CommonTypeSignature<jbyte>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'B'>;
	};

	// `char` type signature.
	template<>
	struct CommonTypeSignature<jchar>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'C'>;
	};

	// `short` type signature.
	template<>
	struct CommonTypeSignature<jshort>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'S'>;
	};

	// `int` type signature.
	template<>
	struct CommonTypeSignature<jint>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'I'>;
	};

	// `long` type signature.
	template<>
	struct CommonTypeSignature<jlong>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'J'>;
	};

	// `float` type signature.
	template<>
	struct CommonTypeSignature<jfloat>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'F'>;
	};

	// `double` type signature.
	template<>
	struct CommonTypeSignature<jdouble>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'D'>;
	};

	// `java.lang.Object` type signature.
	template<>
	struct CommonTypeSignature<jobject>
	{
		// JNI signature.
		using Signature	= Black::JniClassSignatureString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'O', 'b', 'j', 'e', 'c', 't'>;
	};

	// `java.lang.Class` type signature.
	template<>
	struct CommonTypeSignature<jclass>
	{
		// JNI signature.
		using Signature	= Black::JniClassSignatureString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's'>;
	};

	// `java.lang.String` type signature.
	template<>
	struct CommonTypeSignature<jstring>
	{
		// JNI signature.
		using Signature	= Black::JniClassSignatureString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g'>;
	};
}
}
}
}
}
