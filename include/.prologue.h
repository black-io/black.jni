#pragma once


// External dependencies.
#include <black/core.minimal.h>


// The library namespace definition.
#include ".bootstrap/namespace.h"

// Environment configuration.
#include ".bootstrap/configuration.h"

// Isolate the logging for all JNI declarations.
#include ".bootstrap/logging.isolation.h"
#include ".global/logging/logging.h"

// Most global code.
#include ".global/static-strings/signatures.h"
#include ".global/type-traits/IsBitField.h"

// Some forward declarations.
#include "virtual-machine/forwards.h"
#include "handles/forwards.h"
