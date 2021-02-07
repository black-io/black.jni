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
	/**
		@brief	Type translation environment for particular C++ type.

		This context used to properly translate known native C++ type into JNI-consumed type and back from JNI-consumed type.

		@tparam	TNativeType	Native C++ type, for which the translation is required.
	*/
	template< typename TNativeType >
	struct CommonTypeContext;

	// Type translation environment for `void` type.
	template<>
	struct CommonTypeContext<void>;

	// Type translation environment for `bool` type.
	template<>
	struct CommonTypeContext<bool>;

	// Type translation environment for `char16_t` type.
	template<>
	struct CommonTypeContext<char16_t>;

	// Type translation environment for `int8_t` type.
	template<>
	struct CommonTypeContext<int8_t>;

	// Type translation environment for `int16_t` type.
	template<>
	struct CommonTypeContext<int16_t>;

	// Type translation environment for `int32_t` type.
	template<>
	struct CommonTypeContext<int32_t>;

	// Type translation environment for `int64_t` type.
	template<>
	struct CommonTypeContext<int64_t>;

	// Type translation environment for `uint8_t` type.
	template<>
	struct CommonTypeContext<uint8_t>;

	// Type translation environment for `uint16_t` type.
	template<>
	struct CommonTypeContext<uint16_t>;

	// Type translation environment for `uint32_t` type.
	template<>
	struct CommonTypeContext<uint32_t>;

	// Type translation environment for `uint64_t` type.
	template<>
	struct CommonTypeContext<uint64_t>;

	// Type translation environment for `float` type.
	template<>
	struct CommonTypeContext<float>;

	// Type translation environment for `double` type.
	template<>
	struct CommonTypeContext<double>;

	// Type translation environment for `const char*` type.
	template<>
	struct CommonTypeContext<const char*>;

	// Type translation environment for `const char16_t*` type.
	template<>
	struct CommonTypeContext<const char16_t*>;

	// Type translation environment for `std::string_view` type.
	template<>
	struct CommonTypeContext<std::string_view>;

	// Type translation environment for `std::u16string_view` type.
	template<>
	struct CommonTypeContext<std::u16string_view>;

	// Type translation environment for `std::string` type.
	template<>
	struct CommonTypeContext<std::string>;

	// Type translation environment for `std::u16string` type.
	template<>
	struct CommonTypeContext<std::u16string>;

	// Type translation environment for `std::vector` type.
	template< typename TNativeValue, typename TAllocator >
	struct CommonTypeContext<std::vector<TNativeValue, TAllocator>>;
}
}
}
}
}
