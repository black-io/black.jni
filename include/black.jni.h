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
#include "utils/HasBitsField.h"

// Type Marshaling.
#include "marshaling/JavaTypeTraits.h"
#include "marshaling/EnvironmentTraits.h"
#include "marshaling/ArrayTranslationTraits.h"
#include "marshaling/NativeTypeTraits.h"
#include "marshaling/EnumTypeTraits.h"
#include "marshaling/BitfieldTypeTraits.h"

// Most crucial forwards.
#include "utils/forwards.h"
#include "utils/types.h"

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
#include "utils/HandlesCacheEntry.h"
#include "utils/CachedHandles.h"
#include "utils/VirtualMachine.h"
#include "utils/Environment.h"

// Deferred implementation of JNI functionality.
#include "utils/CachedHandles.inl"
#include "utils/VirtualMachine.inl"
#include "utils/Environment.inl"
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
