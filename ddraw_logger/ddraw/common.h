// Copyright (c) 2014 J�r�my Ansel
// Licensed under the MIT license. See LICENSE.txt

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <ddraw.h>
#include <d3d.h>

#include <string>
#include <sstream>

#include "wrapper.h"
#include "logger.h"
#include "utils.h"

// @TheRedDaemon: get return address with _ReturnAddress
#include <intrin.h>
