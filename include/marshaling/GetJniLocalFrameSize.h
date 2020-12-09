#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Internal
{
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


	// Total size of locale frame for JNI environment.
	template< typename... TNativeTypes >
	inline constexpr size_t JNI_LOCAL_FRAME_SIZE = Internal::GetLocalFrameSize<Black::NativeTypeContext<TNativeTypes>::LOCAL_FRAME_SIZE...>();
}
}
}
