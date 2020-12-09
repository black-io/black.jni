#pragma once


namespace Black
{
inline namespace Jni
{
// The marshaling subsystem for JNI library.
inline namespace Marshaling
{
// Internal stuff for JNI marshaling.
namespace Internal
{

}
}
}
}


// JNI Marshaling.
#include "JniTypeSignature.h"
#include "JniTypeContext.h"
#include "JniArrayTranslation.h"
#include "NativeTypeContext.h"

#include "GetJniLocalFrameSize.h"

#include "NativeEnumContext.h"
#include "NativeBitfieldContext.h"
#include "NativeTypeContext.EnumFlags.h"
