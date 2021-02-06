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
	template<>
	struct CommonTypeSignature<void>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'V'>;
	};

	template<>
	struct CommonTypeSignature<jboolean>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'Z'>;
	};

	template<>
	struct CommonTypeSignature<jbyte>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'B'>;
	};

	template<>
	struct CommonTypeSignature<jchar>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'C'>;
	};

	template<>
	struct CommonTypeSignature<jshort>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'S'>;
	};

	template<>
	struct CommonTypeSignature<jint>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'I'>;
	};

	template<>
	struct CommonTypeSignature<jlong>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'J'>;
	};

	template<>
	struct CommonTypeSignature<jfloat>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'F'>;
	};

	template<>
	struct CommonTypeSignature<jdouble>
	{
		// JNI signature.
		using Signature	= Black::StaticString<'D'>;
	};

	template<>
	struct CommonTypeSignature<jobject>
	{
		// JNI signature.
		using Signature	= Black::JniClassSignatureString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'O', 'b', 'j', 'e', 'c', 't'>;
	};

	template<>
	struct CommonTypeSignature<jclass>
	{
		// JNI signature.
		using Signature	= Black::JniClassSignatureString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's'>;
	};

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
