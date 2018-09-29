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
		static_assert( Black::IS_BASE_OF<JniObject, THandle>, "Handle type should be derived from `Black::JniObject`." );

		using ClassPath = typename THandle::ClassPath;

		Black::StringView class_name{ ClassPath::GetData() };
		return { class_name };
	}
}
}
}
