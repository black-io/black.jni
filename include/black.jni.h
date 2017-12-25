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

// Most basic utils.
#include "type-traits/HasBitsField.h"
#include "type-traits/types.h"

// Type Marshaling.
#include "marshaling/JavaTypeTraits.h"
#include "marshaling/EnvironmentTraits.h"
#include "marshaling/ArrayTranslationTraits.h"
#include "marshaling/NativeTypeTraits.h"
#include "marshaling/EnumTypeTraits.h"
#include "marshaling/BitfieldTypeTraits.h"

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
#include "marshaling/NativeTypeTraits.FromJava.inl"
#include "marshaling/NativeTypeTraits.ToJava.inl"
#include "marshaling/ArrayTranslationTraits.FromJava.inl"
#include "marshaling/ArrayTranslationTraits.ToJava.inl"
