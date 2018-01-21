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

// JNI handles.
#include "handles/JniClass.h"
#include "marshaling/NativeTypeContext.JniClass.h"

#include "handles/JniObject.h"
#include "marshaling/NativeTypeContext.JniObject.h"
#include "marshaling/NativeObjectContext.h"

#include "handles/JniMemberField.h"
#include "handles/JniStaticField.h"

#include "handles/MemberFunctionEntry.h"
#include "handles/JniMemberFunction.h"

#include "handles/StaticFunctionEntry.h"
#include "handles/JniStaticFunction.h"

// JNI native function specification.
#include "utils/NativeFunction.h"
#include "utils/JniNativeBindingTable.h"

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
#include "handles/JniObject.inl"
#include "handles/JniMemberField.inl"
#include "handles/JniStaticField.inl"
#include "handles/JniMemberFunction.inl"
#include "handles/JniStaticFunction.inl"
#include "handles/MemberFunctionEntry.inl"
#include "handles/StaticFunctionEntry.inl"
#include "marshaling/NativeTypeContext.FromJni.inl"
#include "marshaling/NativeTypeContext.ToJni.inl"
#include "marshaling/JniArrayTranslation.FromJni.inl"
#include "marshaling/JniArrayTranslation.ToJni.inl"

// Remove local logging overrides if necessary.
#include "utils/logging.isolation.h"
