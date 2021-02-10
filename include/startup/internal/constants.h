#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
namespace Internal
{
	// Tagging type to mark the JNI-session static storage. This storage carries the memory until `JNI_OnUnload` call.
	enum class JniSessionStorage;
}
}
}
}
