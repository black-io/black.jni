#pragma once


// External dependencies.
// JniObject implements the interface of `Black::Mutex`.
#include <black/core/concurrency.h>


namespace Black
{
inline namespace Jni
{
// Java object handles subsystem.
inline namespace Handles
{
// Internal stuff for JNI handles.
namespace Internal
{

}

// Field handles coalition.
inline namespace Fields
{
	// Alias the internal stuff.
	namespace Internal = Black::Jni::Handles::Internal;
}

// Function handles coalition.
inline namespace Functions
{
	// Alias the internal stuff.
	namespace Internal = Black::Jni::Handles::Internal;
}

// Object handles coalition.
inline namespace Objects
{
	// Alias the internal stuff.
	namespace Internal = Black::Jni::Handles::Internal;
}
}
}
}


// Most fundamental internal stuff.
#include "internal/forwards.h"
#include "internal/ObjectStateBuffer.h"
#include "internal/ObjectState.h"

// JNI objects.
#include "objects/forwards.h"

#include "objects/JniClass.h"
#include "objects/JniObject.h"

#include "internal/ClassHandleJniConverter.h"
#include "internal/ObjectHandleJniConverter.h"
#include "internal/ObjectJniConverter.h"

// JNI field handles.
#include "fields/JniMemberField.h"
#include "fields/JniStaticField.h"

// JNI Function handles.
#include "internal/MemberFunctionEntry.h"
#include "internal/StaticFunctionEntry.h"

#include "functions/JniMemberFunction.h"
#include "functions/JniStaticFunction.h"

// Performance-support tools.
#include "internal/ClassRegistry.h"
#include "internal/ObjectStateRegistry.h"

// Deferred implementations.
#include "internal/ObjectStateRegistry.inl"

#include "functions/JniStaticFunction.inl"
#include "functions/JniMemberFunction.inl"

#include "internal/StaticFunctionEntry.inl"
#include "internal/MemberFunctionEntry.inl"

#include "fields/JniStaticField.inl"
#include "fields/JniMemberField.inl"

#include "objects/JniObject.inl"
#include "objects/JniClass.inl"

#include "internal/ObjectState.inl"
#include "internal/ObjectStateBuffer.inl"
