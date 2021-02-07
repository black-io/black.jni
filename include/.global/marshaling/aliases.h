#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Global
{
inline namespace Marshaling
{
	/**
		@brief	JNI-style type signature for common JNI types.

		This signature valid only for common JNI type, such as `jint`, `jclass` or `jstring`.

		@tparam	TJniType	Regular JNI type.
	*/
	template< typename TJniType >
	using JniCommonTypeSignature = Internal::CommonTypeSignature<TJniType>;

	/**
		@brief	JNI-style type signature of common JNI function.

		This signature valid only for common JNI type, such as `jint`, `jclass` or `jstring`.

		@tparam	TJniResult		Type of function result.
		@tparam	TJniArguments	Parameter pack of function argument types.
	*/
	template< typename TJniResult, typename... TJniArguments >
	using JniCommonTypeFunctionSignature = Black::JniFunctionSignatureString<JniCommonTypeSignature<TJniResult>, JniCommonTypeSignature<TJniArguments>...>;

	/**
		@brief	Interface mapping of `JNIEnv` to work with given common JNI type.

		This mapping may be used for direct interaction with `JNIEnv` in order to operate with value of given JNI type.
		The mapping is valid only for common JNI types, such as `jint`, `jclass` or `jstring`.

		@tparam	TJniType	Regular JNI type.
	*/
	template< typename TJniType >
	using JniCommonTypeEnvContext = Internal::CommonTypeJniContext<TJniType>;

	/**
		@brief	Converter for arrays of native types.

		This converter may be used to operate on array values. It uses given converter for array element.

		@tparam	TElementConverter	Type converter of array element.
	*/
	template< typename TElementConverter >
	using JniArrayConverter = Internal::ArrayTypeConverter<TElementConverter, TElementConverter::IS_PLAIN>;

	/**
		@brief	Suitable JNI converter for given native type.

		Any user-defined type may be equipped with its owned converter. To do that, there should be declared ADL-visible function
		with name `GetJniConverter` and signature like `JniConverter GetJniConverter( NativeType )`. No definition is required for function,
		the declaration would be enough.

		Some user-defined types, like valid bit-fields, enumeration types or instantiations of `Black::EnumFlags`, have predefined converter,
		but one always could declare custom converter to specify the unique conversion technique for the type.

		The user-defined converter should satisfy the requirements of JNI converter.
		* Inner type `Signature` should be defined with valid class path string of Java-side type.
		* Valid interface mapping of `JNIEnv` should be provided through the scope of converter.
		* Inner constant `LOCAL_FRAME_SIZE` should specify the size of stack frame the Java-side object occupy.
		* Inner type `NativeType` should match the native type this converter works with.
		* Inner type `JniType` should identify the common JNI type the native type maps.
		* Static function `FromJni` should implement the conversion from value of `JniType` into value of `NativeType`.
		* Static function `ToJni` should implement the conversion from value of `NativeType` into value of `JniType`.

		For more information about JNI converter requirements one could investigate the implementation of `CommonTypeJniConverter` template.

		@tparam	TNativeType	Native C++ type to be converted.
	*/
	template< typename TNativeType >
	using JniNativeTypeConverter = typename Internal::NativeTypeConverterSelector<TNativeType>::Converter;

	/**
		@brief	Common JNI type corresponded to given native type.

		The type aliased is the usable type that may be given from Java side or sent to Java side.
		The value of given native type may be converted to value of this JNI type using the converter or conversion functions.

		@tparam	TNativeType	Native C++ type to be translated int JNI type.
	*/
	template< typename TNativeType >
	using JniType = typename JniNativeTypeConverter<TNativeType>::JniType;

	/**
		@brief	JNI-style type signature corresponded to given native type.

		This signature may be used to operate with JNI environment.

		@tparam	TNativeType	Native C++ type.
	*/
	template< typename TNativeType >
	using JniTypeSignature = typename JniNativeTypeConverter<TNativeType>::Signature;

	/**
		@brief	JNI-style function signature for any native function.

		This signature is be valid JNI-style signature of given function.

		@tparam	TNativeResult		Type of function result.
		@tparam	TNativeArguments	Parameter pack of function argument types.
	*/
	template< typename TNativeResult, typename... TNativeArguments >
	using JniTypeFunctionSignature = Black::JniFunctionSignatureString<JniTypeSignature<TNativeResult>, JniTypeSignature<TNativeArguments>...>;
}
}
}
}
