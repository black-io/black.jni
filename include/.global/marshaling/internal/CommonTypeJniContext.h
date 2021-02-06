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
	// Context for JNIEnv to operate with common JNI type.
	template< typename TJniType >
	struct CommonTypeJniContext;

	// JNI environment for `void` type.
	template<>
	struct CommonTypeJniContext<void>;

	// JNI environment for `boolean` type.
	template<>
	struct CommonTypeJniContext<jboolean>;

	// JNI environment for `byte` type.
	template<>
	struct CommonTypeJniContext<jbyte>;

	// JNI environment for `char` type.
	template<>
	struct CommonTypeJniContext<jchar>;

	// JNI environment for `short` type.
	template<>
	struct CommonTypeJniContext<jshort>;

	// JNI environment for `int` type.
	template<>
	struct CommonTypeJniContext<jint>;

	// JNI environment for `long` type.
	template<>
	struct CommonTypeJniContext<jlong>;

	// JNI environment for `float` type.
	template<>
	struct CommonTypeJniContext<jfloat>;

	// JNI environment for `double` type.
	template<>
	struct CommonTypeJniContext<jdouble>;

	// JNI environment for any type derived from `java.lang.Object`.
	template<>
	struct CommonTypeJniContext<jobject>;
}
}
}
}
}
