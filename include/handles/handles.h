#pragma once


// External dependencies.
// JniObject implements the interface of `Black::Mutex`.
#include <black/core/concurrency.h>


// Namespace declaration.
#include "namespace.h"


// JNI handles.
#include "JniClass.h"
#include "marshaling/NativeTypeContext.JniClass.h"

#include "internal/SharedStateStorage.h"
#include "internal/SharedState.h"
#include "JniObject.h"
#include "marshaling/NativeTypeContext.JniObject.h"
#include "marshaling/NativeObjectContext.h"

#include "JniMemberField.h"
#include "JniStaticField.h"

#include "MemberFunctionEntry.h"
#include "JniMemberFunction.h"

#include "StaticFunctionEntry.h"
#include "JniStaticFunction.h"
