#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Internal
{
	// Safe environment context for object handle.
	template< typename TObjectHandle, bool IS_VALID_HANDLE >
	struct ObjectContext;

	// JNI environment context for object handle.
	template< typename TObjectHandle >
	struct ObjectContext<TObjectHandle, true> : JniContext<jobject>
	{
		// Count of local references required to store this type in JNI local frame.
		static constexpr size_t	LOCAL_FRAME_SIZE = 1;

		// JNI type signature.
		using Signature		= Black::StaticStringJoin<Black::StaticString<'L'>, typename TObjectHandle::ClassPath, Black::StaticString<';'>>;

		// C++ native type.
		using NativeType	= TObjectHandle;

		// JNI type
		using JniType		= jobject;

		// Type translation from JNI space to C++ space.
		static inline void FromJni( const JniType& source, NativeType& destination )	{ destination = source; };

		// Type translation from C++ space to JNI space.
		static inline void ToJni( const NativeType& source, JniType& destination )		{ destination = *source; };
	};
}


	// JNI environment context for object handle.
	template< typename TObjectHandle >
	using NativeObjectContext = Internal::ObjectContext<TObjectHandle, Black::IS_BASE_OF<Black::JniObject, TObjectHandle>>;
}
}
}
