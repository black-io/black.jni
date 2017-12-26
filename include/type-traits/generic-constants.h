#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace TypeTraits
{
namespace Traits
{
	// Common path to check the non-bit-field types.
	template< typename TBitfield, typename = int >
	struct HasBitsField : std::false_type
	{

	};

	// Path to check that the given type has required field for bit-fields.
	template< typename TBitfield >
	struct HasBitsField<TBitfield, decltype( (void)TBitfield::bits, 0 )> : std::true_type
	{

	};
}


	// Bit-field type check.
	template< typename TCondition >
	constexpr bool IS_BIT_FIELD = Traits::HasBitsField<TCondition>::value;
}
}
}
