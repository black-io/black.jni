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
		@brief	Regular converting function from Jni type to C++ one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, JNI-side.
		@param	destination	Final storage of converted value, C++-side.
	*/
	template< typename TNativeType >
	inline void ConvertFromJni( const JniType<TNativeType>& source, TNativeType& destination );

	/**
		@brief	Regular converting function from C++ type to Jni one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, C++-side.
		@param	destination	Final storage of converted value, Jni-side.
	*/
	template< typename TNativeType >
	inline void ConvertToJni( const TNativeType& source, JniType<TNativeType>& destination );

	/**
		@brief	NRVO-optimizable converting function from Jni type to C++ one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, Jni-side.
		@return				Final storage of converted value, C++-side.
	*/
	template< typename TNativeType >
	inline TNativeType ConvertFromJni( const JniType<TNativeType>& source );

	/**
		@brief	NRVO-optimizable converting function from C++ type to Java one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, C++-side.
		@return				Final storage of converted value, Java-side.
	*/
	template< typename TNativeType >
	inline JniType<TNativeType> ConvertToJni( const TNativeType& source );

	/**
		@brief	Helper function to calculate the size of local frame in Java to store the local references of given native types.

		@tparam	TNativeTypes	Parameter pack of required types to be stored in Java local frame.
	*/
	template< typename... TNativeTypes >
	inline constexpr size_t CalculateLocalFrameSize();
}
}
}
}
