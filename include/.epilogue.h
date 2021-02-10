#pragma once


// Deferred implementations.
#include ".global/marshaling/functions.inl"

#include ".global/marshaling/internal/CommonTypeJniConverter.inl"
#include ".global/marshaling/internal/CommonTypeJniConverter.FromJni.inl"
#include ".global/marshaling/internal/CommonTypeJniConverter.ToJni.inl"
#include ".global/marshaling/internal/ArrayTypeConverter.inl"
#include ".global/marshaling/internal/CommonTypeJniContext.inl"
#include ".global/marshaling/internal/CommonTypeSignature.inl"

// Restore the state of logging macros.
#include ".bootstrap/logging.restoration.h"
