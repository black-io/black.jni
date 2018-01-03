#pragma once

// Dependencies.
#include <black.core.h>


namespace Black
{
// Black::Jni library.
inline namespace Jni
{

}
}

// Cut off the compilation in case of target platform is not Android.
#if( !BLACK_ANDROID_PLATFORM )
	#error Black::Jni was designed for Android OS only! Be sure to exclude it from build for other target platforms.
#endif

// Local overrides for logging stuff.
#include "utils/logging.h"

// Most basic utils and traits.
#include "type-traits/StaticStrings.jni.h"

// Type Marshaling.
#include "marshaling/JniTypeSignature.h"
#include "marshaling/JniTypeContext.h"
#include "marshaling/JniArrayTranslation.h"
#include "marshaling/NativeTypeContext.h"

#include "type-traits/generic-constants.h"

#include "marshaling/NativeEnumContext.h"
#include "marshaling/NativeBitfieldContext.h"
#include "marshaling/NativeTypeContext.EnumFlags.h"

// Most crucial forwards.
#include "virtual-machine/forwards.h"

// JNI classes.
#include "handles/Class.h"
#include "handles/Object.h"
#include "marshaling/NativeTypeTraits.Object.h"
#include "marshaling/NativeTypeTraits.Class.h"
#include "marshaling/ObjectTypeTraits.h"

// JNI member fields.
#include "handles/MemberField.h"
#include "handles/StaticField.h"

// JNI member functions.
#include "utils/MemberFunctionInvocation.h"
#include "utils/StaticFunctionInvocation.h"
#include "handles/MemberFunction.h"
#include "handles/StaticFunction.h"

// JNI native function specification.
#include "utils/NativeFunction.h"
#include "utils/NativeFunction.utils.h"
#include "utils/NativeFunction.macros.h"

// JNI Virtual machine and environment.
#include "virtual-machine/HandlesCacheEntry.h"
#include "virtual-machine/CachedHandles.h"
#include "virtual-machine/VirtualMachine.h"
#include "virtual-machine/Environment.h"

// Deferred implementation of JNI functionality.
#include "virtual-machine/CachedHandles.inl"
#include "virtual-machine/VirtualMachine.inl"
#include "virtual-machine/Environment.inl"
#include "utils/NativeFunction.utils.inl"
#include "handles/Object.inl"
#include "handles/MemberField.inl"
#include "handles/StaticField.inl"
#include "handles/MemberFunction.inl"
#include "handles/StaticFunction.inl"
#include "utils/MemberFunctionInvocation.inl"
#include "utils/StaticFunctionInvocation.inl"
#include "marshaling/NativeTypeContext.FromJni.inl"
#include "marshaling/NativeTypeContext.ToJni.inl"
#include "marshaling/JniArrayTranslation.FromJni.inl"
#include "marshaling/JniArrayTranslation.ToJni.inl"

// Remove local logging overrides if necessary.
#include "utils/logging.isolation.h"
