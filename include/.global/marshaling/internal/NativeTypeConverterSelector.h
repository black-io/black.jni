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
	// Selection type to determine the proper converter for given known type.
	template< typename TNativeType, typename = void >
	struct KnownNativeTypeConverterSelector final
	{
		// By default the common type converter will be used.
		using Converter = CommonTypeContext<TNativeType>;
	};

	// The selection variant to use predefined converter for enumeration types.
	template< typename TEnumeration >
	struct KnownNativeTypeConverterSelector<TEnumeration, std::enable_if_t<std::is_enum_v<TEnumeration>>> final
	{
		// Predefined converter for enumeration types will be used.
		using Converter = EnumJniConverter<TEnumeration>;
	};

	// The selection variant to use predefined converter for bit-fields.
	template< typename TBitfield >
	struct KnownNativeTypeConverterSelector<TBitfield, std::enable_if_t<Black::IS_BIT_FIELD<TBitfield>>> final
	{
		// Predefined bit-field converter will be used.
		using Converter = BitfieldJniConverter<TBitfield>;
	};

	// The selection variant to use predefined converter for `Black::EnumFlags` instantiations.
	template< typename TEnumeration, typename TProjection >
	struct KnownNativeTypeConverterSelector<Black::EnumFlags<TEnumeration, TProjection>, void> final
	{
		// Predefined converter for `Black::EnumFlags` will be used.
		using Converter = EnumFlagsJniConvertter<TEnumeration, TProjection>;
	};

	// Custom converter type selector.
	template< typename TNativeType >
	struct CustomNativeTypeConverterSelector final
	{
		// There should be ADL-reachable function declaration with name `GetJniConverter` and argument of `TNativeType`.
		using Converter = std::decay_t<decltype( GetJniConverter( std::declval<TNativeType>() ) )>;
	};

	// Selection type to determine the proper type converter for given native type.
	template< typename TNativeType, typename = void >
	struct NativeTypeConverterSelector
	{
		// By default try to search the predefined converter for known types.
		using Converter = typename KnownNativeTypeConverterSelector<TNativeType>::Converter;
	};

	// The selection variant to use found custom converter for given type.
	template< typename TNativeType >
	struct NativeTypeConverterSelector<TNativeType, std::void_t<decltype( GetJniConverter( std::declval<TNativeType>() ) )>>
	{
		// Locate the type of custom converter.
		using Converter = typename CustomNativeTypeConverterSelector<TNativeType>::Converter;
	};
}
}
}
}
}
