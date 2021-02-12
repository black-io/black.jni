#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Global
{
inline namespace TypeTraits
{
namespace Internal
{
	// Common path to check the non-bit-field types.
	template< typename TBitfield, typename = void >
	struct HasBitsField : std::false_type
	{

	};

	// Path to check that the given type has required field for bit-fields.
	// In case of `TBitfield` has no `bits` member, the deducing will fall into common path with `false` result.
	// Additional checks may be implemented for this path, if needed.
	template< typename TBitfield >
	struct HasBitsField<TBitfield, std::void_t<decltype( std::declval<TBitfield>().bits )>> : std::is_integral<decltype( std::declval<TBitfield>().bits )>
	{

	};
}


	/**
		@brief	Type trait the indicate that given arbitrary type represents a bit-field.
		The value of constant is `true` only when the given type has `bits` field inside.
		The type of `TCandidate::bits` field is not checked.
		@tparam	TCandidate	The candidate type to check.
	*/
	template< typename TCandidate >
	inline constexpr bool IS_BIT_FIELD = std::is_union_v<TCandidate> && Internal::HasBitsField<TCandidate>::value;
}
}
}
}
