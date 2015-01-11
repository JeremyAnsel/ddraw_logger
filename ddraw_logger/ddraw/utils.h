// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#pragma once

#include <string>
#include <guiddef.h>

#define STR_ENUM(flags, E, V) if(flags & E ## _ ## V) { str << " " # V; }

std::string tostr_HR(HRESULT hr);
std::string tostr_GUID(const GUID* lpGUID);
std::string tostr_RECT(LPRECT lpRect);
std::string tostr_DDSURFACEDESC(LPDDSURFACEDESC lpDDSurfaceDesc);
std::string tostr_D3DRECT(LPD3DRECT lpRect);
