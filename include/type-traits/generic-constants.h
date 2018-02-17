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
	// In case of `TBitfield` has no `bits` member, the deducing will fall into common path with `false` result.
	// Additional checks may be implemented for this path, if needed.
	template< typename TBitfield >
	struct HasBitsField<TBitfield, decltype( (void)TBitfield::bits, 0 )> : std::true_type
	{

	};

	// Get the total size of local frame for JNI environment.
	template< size_t FRAME_SIZE >
	constexpr size_t GetLocalFrameSize()
	{
		return FRAME_SIZE;
	}

	// Get the total size of local frame for JNI environment.
	template< size_t FRAME_SIZE, size_t... REST_SIZES >
	constexpr size_t GetLocalFrameSize( BLACK_SFINAE( sizeof...( REST_SIZES ) > 0 ) )
	{
		return FRAME_SIZE + GetLocalFrameSize<REST_SIZES...>();
	}

	// Shortcut for empty list of frame sizes. Returns null.
	template< size_t... FRAME_SIZES >
	constexpr size_t GetLocalFrameSize( BLACK_SFINAE( sizeof...( FRAME_SIZES ) == 0 ) )
	{
		return 0;
	}
}


	// Bit-field type check.
	template< typename TCondition >
	constexpr bool IS_BIT_FIELD = Traits::HasBitsField<TCondition>::value;

	// Total size of locale frame for JNI environment.
	template< typename... TNativeTypes >
	constexpr size_t JNI_LOCAL_FRAME_SIZE = Traits::GetLocalFrameSize<Black::NativeTypeContext<TNativeTypes>::LOCAL_FRAME_SIZE...>();
}
}
}
