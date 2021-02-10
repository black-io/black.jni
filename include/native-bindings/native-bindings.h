#pragma once


namespace Black
{
inline namespace Jni
{
// Native function binding subsystem.
inline namespace NativeBindings
{
// Internal stuff for native bindings.
namespace Internal
{

}
}
}
}


// Most fundamental internal stuff.
#include "internal/NativeMethodBuilder.h"

// Public functions.
#include "functions.h"

// Deferred implementations.
#include "functions.inl"

#include "internal/NativeMethodBuilder.inl"
