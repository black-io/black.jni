#pragma once


// External dependencies.
#include <black/core.h>
#include <black/core/algorithms.h>
#include <black/core/static-strings.h>


// The library namespace definition.
#include ".bootstrap/namespace.h"

// Environment configuration.
#include ".bootstrap/configuration.h"

// Most global code.
#include ".global/static-strings/signatures.h"
#include ".global/type-traits/IsBitField.h"

// Persistent stuff.
#include ".global/jni-connections/internal/structures.h"
#include ".global/jni-connections/internal/JniConnectionInitializer.h"
#include ".global/jni-connections/JniConnection.h"
#include ".global/jni-connections/JniEnvironment.h"

// JNI Marshaling.
#include ".global/marshaling/internal/CommonTypeSignature.h"
#include ".global/marshaling/internal/CommonTypeJniContext.h"
#include ".global/marshaling/internal/ArrayTypeConverter.h"
#include ".global/marshaling/internal/CommonTypeJniConverter.h"

#include ".global/marshaling/internal/EnumJniConverter.h"
#include ".global/marshaling/internal/BitfieldJniConverter.h"
#include ".global/marshaling/internal/EnumFlagsJniConvertter.h"

#include ".global/marshaling/internal/NativeTypeConverterSelector.h"
#include ".global/marshaling/aliases.h"
#include ".global/marshaling/functions.h"
