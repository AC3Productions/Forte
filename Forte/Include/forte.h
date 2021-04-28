// file:   forte.h
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  General include file. All header files should include this file.

#ifndef FORTE_H
#define FORTE_H

// For deliberately suppressing Unreferenced Parameter warnings.
#define UNREF_PARAM(x) (x)

// C++ libraries
#include <string>
#include <exception>

// raylib, the library for everything basically
#include "raylib-cpp.hpp"
typedef raylib::Vector2 RVec2; // shorthand for vectors

// Trace logging should happen everywhere
#include <trace.h>

#endif