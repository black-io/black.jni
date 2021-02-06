#pragma once


// Fundamental external dependencies.
#include <black/core/static-lists.h>


namespace Black
{
inline namespace Jni
{
// JNI startup entities.
inline namespace Startup
{
// Internal stuff for startup subsystem.
namespace Internal
{

}
}
}
}


// Most fundamental stuff.
#include "internal/BasicStartupNode.h"
#include "internal/FunctionalStartupNode.h"
#include "internal/FunctionalShutdownNode.h"

#include "internal/StartupStaticList.h"

// Entity for startup list.
#include "JniStartupEntity.h"
#include "JniShutdownEntity.h"

// Deferred implementations.
#include "JniShutdownEntity.inl"
#include "JniStartupEntity.inl"

#include "internal/FunctionalShutdownNode.inl"
#include "internal/FunctionalStartupNode.inl"
