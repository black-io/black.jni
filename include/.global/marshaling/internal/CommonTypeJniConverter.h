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
	struct CommonTypeJniConverter;

	// Type translation environment for `void` type.
	template<>
	struct CommonTypeJniConverter<void>;

	// Type translation environment for `bool` type.
	template<>
	struct CommonTypeJniConverter<bool>;

	// Type translation environment for `char16_t` type.
	template<>
	struct CommonTypeJniConverter<char16_t>;

	// Type translation environment for `int8_t` type.
	template<>
	struct CommonTypeJniConverter<int8_t>;

	// Type translation environment for `int16_t` type.
	template<>
	struct CommonTypeJniConverter<int16_t>;

	// Type translation environment for `int32_t` type.
	template<>
	struct CommonTypeJniConverter<int32_t>;

	// Type translation environment for `int64_t` type.
	template<>
	struct CommonTypeJniConverter<int64_t>;

	// Type translation environment for `uint8_t` type.
	template<>
	struct CommonTypeJniConverter<uint8_t>;

	// Type translation environment for `uint16_t` type.
	template<>
	struct CommonTypeJniConverter<uint16_t>;

	// Type translation environment for `uint32_t` type.
	template<>
	struct CommonTypeJniConverter<uint32_t>;

	// Type translation environment for `uint64_t` type.
	template<>
	struct CommonTypeJniConverter<uint64_t>;

	// Type translation environment for `float` type.
	template<>
	struct CommonTypeJniConverter<float>;

	// Type translation environment for `double` type.
	template<>
	struct CommonTypeJniConverter<double>;

	// Type translation environment for `const char*` type.
	template<>
	struct CommonTypeJniConverter<const char*>;

	// Type translation environment for `const char16_t*` type.
	template<>
	struct CommonTypeJniConverter<const char16_t*>;

	// Type translation environment for `std::string_view` type.
	template<>
	struct CommonTypeJniConverter<std::string_view>;

	// Type translation environment for `std::u16string_view` type.
	template<>
	struct CommonTypeJniConverter<std::u16string_view>;

	// Type translation environment for `std::string` type.
	template<>
	struct CommonTypeJniConverter<std::string>;

	// Type translation environment for `std::u16string` type.
	template<>
	struct CommonTypeJniConverter<std::u16string>;

	// Type translation environment for `std::vector` type.
	template< typename TNativeValue, typename TAllocator >
	struct CommonTypeJniConverter<std::vector<TNativeValue, TAllocator>>;
}
}
}
}
}
