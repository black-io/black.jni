#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	template< typename THandle >
	inline JniClass JniClass::FromHandleType()
	{
		static_assert( std::is_base_of_v<JniObject, THandle>, "Handle type should be derived from `Black::JniObject`." );

		using ClassPath = typename THandle::ClassPath;

		std::string_view class_name{ ClassPath::GetData() };
		return { class_name };
	}
}
}
}
