#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	// JNI environment context for any regular JNI type.
	template< typename TJniType >
	struct JniContext;

	// JNI environment context for `void` type.
	template<>
	struct JniContext<void>
	{
		// Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallVoidMethod;

		// Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticVoidMethod;

		// Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualVoidMethod;
	};

	// JNI environment context for `boolean` type.
	template<>
	struct JniContext<jboolean>
	{
		// Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		// Type of JNI array representation, which can be consumed by array functions.
		using ArrayType											= jbooleanArray;

		// Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewBooleanArray;

		// Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetBooleanArrayElements;

		// Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetBooleanArrayRegion;

		// Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseBooleanArrayElements;

		// Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetBooleanArrayRegion;

		// Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetBooleanField;

		// Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetBooleanField;

		// Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticBooleanField;

		// Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticBooleanField;

		// Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallBooleanMethod;

		// Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticBooleanMethod;

		// Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualBooleanMethod;
	};

	// JNI environment context for `byte` type.
	template<>
	struct JniContext<jbyte>
	{
		// Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		// Type of JNI array representation, which can be consumed by array functions.
		using ArrayType											= jbyteArray;

		// Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewByteArray;

		// Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetByteArrayElements;

		// Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetByteArrayRegion;

		// Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseByteArrayElements;

		// Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetByteArrayRegion;

		// Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetByteField;

		// Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetByteField;

		// Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticByteField;

		// Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticByteField;

		// Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallByteMethod;

		// Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticByteMethod;

		// Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualByteMethod;
	};

	// JNI environment context for `char` type.
	template<>
	struct JniContext<jchar>
	{
		// Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		// Type of JNI array representation, which can be consumed by array functions.
		using ArrayType											= jcharArray;

		// Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewCharArray;

		// Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetCharArrayElements;

		// Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetCharArrayRegion;

		// Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseCharArrayElements;

		// Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetCharArrayRegion;

		// Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetCharField;

		// Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetCharField;

		// Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticCharField;

		// Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticCharField;

		// Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallCharMethod;

		// Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticCharMethod;

		// Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualCharMethod;
	};

	// JNI environment context for `short` type.
	template<>
	struct JniContext<jshort>
	{
		// Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		// Type of JNI array representation, which can be consumed by array functions.
		using ArrayType											= jshortArray;

		// Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewShortArray;

		// Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetShortArrayElements;

		// Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetShortArrayRegion;

		// Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseShortArrayElements;

		// Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetShortArrayRegion;

		// Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetShortField;

		// Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetShortField;

		// Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticShortField;

		// Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticShortField;

		// Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallShortMethod;

		// Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticShortMethod;

		// Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualShortMethod;
	};

	// JNI environment context for `int` type.
	template<>
	struct JniContext<jint>
	{
		// Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		// Type of JNI array representation, which can be consumed by array functions.
		using ArrayType											= jintArray;

		// Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewIntArray;

		// Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetIntArrayElements;

		// Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetIntArrayRegion;

		// Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseIntArrayElements;

		// Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetIntArrayRegion;

		// Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetIntField;

		// Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetIntField;

		// Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticIntField;

		// Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticIntField;

		// Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallIntMethod;

		// Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticIntMethod;

		// Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualIntMethod;
	};

	// Private specification for `long` type.
	template<>
	struct JniContext<jlong>
	{
		// Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		// Type of JNI array representation, which can be consumed by array functions.
		using ArrayType											= jlongArray;

		// Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewLongArray;

		// Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetLongArrayElements;

		// Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetLongArrayRegion;

		// Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseLongArrayElements;

		// Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetLongArrayRegion;

		// Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetLongField;

		// Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetLongField;

		// Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticLongField;

		// Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticLongField;

		// Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallLongMethod;

		// Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticLongMethod;

		// Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualLongMethod;
	};

	// Private specification for `float` type.
	template<>
	struct JniContext<jfloat>
	{
		// Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		// Type of JNI array representation, which can be consumed by array functions.
		using ArrayType											= jfloatArray;

		// Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewFloatArray;

		// Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetFloatArrayElements;

		// Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetFloatArrayRegion;

		// Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseFloatArrayElements;

		// Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetFloatArrayRegion;

		// Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetFloatField;

		// Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetFloatField;

		// Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticFloatField;

		// Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticFloatField;

		// Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallFloatMethod;

		// Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticFloatMethod;

		// Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualFloatMethod;
	};

	// Private specification for `double` type.
	template<>
	struct JniContext<jdouble>
	{
		// Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		// Type of JNI array representation, which can be consumed by array functions.
		using ArrayType											= jdoubleArray;

		// Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewDoubleArray;

		// Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetDoubleArrayElements;

		// Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetDoubleArrayRegion;

		// Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseDoubleArrayElements;

		// Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetDoubleArrayRegion;

		// Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetDoubleField;

		// Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetDoubleField;

		// Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticDoubleField;

		// Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticDoubleField;

		// Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallDoubleMethod;

		// Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticDoubleMethod;

		// Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualDoubleMethod;
	};

	// Private specification for any type derived from `java.lang.Object`.
	template<>
	struct JniContext<jobject>
	{
		// Is this type plain?
		static constexpr bool IS_PLAIN							= false;

		// Type of JNI array representation, which can be consumed by array functions.
		using ArrayType											= jobjectArray;

		// Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewObjectArray;

		// Array elements getter.
		static constexpr auto ARRAY_ELEMENT_READ_HANDLER		= &JNIEnv::GetObjectArrayElement;

		// Array region setter.
		static constexpr auto ARRAY_ELEMENT_WRITE_HANDLER		= &JNIEnv::SetObjectArrayElement;

		// Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetObjectField;

		// Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetObjectField;

		// Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticObjectField;

		// Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticObjectField;

		// Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallObjectMethod;

		// Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticObjectMethod;

		// Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualObjectMethod;
	};
}


	// JNI environment context for any regular JNI type.
	template< typename TJniType >
	using JniTypeContext = Traits::JniContext<TJniType>;
}
}
}
