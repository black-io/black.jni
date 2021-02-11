#pragma once


// Deferred implementations.
#include ".global/marshaling/functions.inl"

#include ".global/marshaling/internal/CommonTypeJniConverter.FromJni.inl"
#include ".global/marshaling/internal/CommonTypeJniConverter.ToJni.inl"
#include ".global/marshaling/internal/ArrayTypeConverter.inl"

// Restore the state of logging macros.
#include ".bootstrap/logging.restoration.h"
