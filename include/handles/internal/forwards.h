#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
	// Forward declaration of custom JNI converter for class handles.
	struct ClassHandleJniConverter;

	// Forward declaration of custom JNI converter for object handles.
	struct ObjectHandleJniConverter;

	// Forward declaration of custom JNI converter template for any derived object handle.
	template< typename TObjectHandle >
	struct ObjectJniConverter;
}
}
}
}
