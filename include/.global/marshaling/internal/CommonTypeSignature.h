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
	struct CommonTypeSignature<void>;

	// `boolean` type signature.
	template<>
	struct CommonTypeSignature<jboolean>;

	// `byte` type signature.
	template<>
	struct CommonTypeSignature<jbyte>;

	// `char` type signature.
	template<>
	struct CommonTypeSignature<jchar>;

	// `short` type signature.
	template<>
	struct CommonTypeSignature<jshort>;

	// `int` type signature.
	template<>
	struct CommonTypeSignature<jint>;

	// `long` type signature.
	template<>
	struct CommonTypeSignature<jlong>;

	// `float` type signature.
	template<>
	struct CommonTypeSignature<jfloat>;

	// `double` type signature.
	template<>
	struct CommonTypeSignature<jdouble>;

	// `java.lang.Object` type signature.
	template<>
	struct CommonTypeSignature<jobject>;

	// `java.lang.Class` type signature.
	template<>
	struct CommonTypeSignature<jclass>;

	// `java.lang.String` type signature.
	template<>
	struct CommonTypeSignature<jstring>;
}
}
}
}
}
