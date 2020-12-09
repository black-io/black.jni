#pragma once


// The prologue of library.
#include ".prologue.h"

#include "marshaling/marshaling.h"
#include "handles/handles.h"
#include "virtual-machine/virtual-machine.h"

// Deferred implementations.
#include "virtual-machine/virtual-machine.inl"
#include "handles/handles.inl"
#include "marshaling/marshaling.inl"

// The epilogue of library.
#include ".epilogue.h"
