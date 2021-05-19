// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#include "common.h"
#include "DirectDraw.h"
#include "DirectDraw2.h"
#include "DirectDraw4.h"
#include "DirectDrawClipper.h"
#include "DirectDrawPalette.h"
#include "DirectDrawSurface.h"
#include "Direct3D.h"

DirectDraw::DirectDraw(IDirectDraw* original)
{
	this->_original = original;
}

DirectDraw::~DirectDraw()
{
	RemoveWrapper(this->_original);
}

HRESULT DirectDraw::QueryInterface(
	REFIID riid,
	LPVOID* obp
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << tostr_GUID(&riid);

	HRESULT hr = this->_original->QueryInterface(riid, obp);

	if (SUCCEEDED(hr))
	{
		void* wrapper = GetWrapper(*obp);

		if (wrapper)
		{
			*obp = wrapper;
		}
		else if (riid == IID_IDirectDraw2)
		{
			*obp = CreateWrapperT(DirectDraw2, *obp);
		}
		else if (riid == IID_IDirectDraw4)
		{
			*obp = CreateWrapperT(DirectDraw4, *obp);
		}
		else if (riid == IID_IDirect3D)
		{
			*obp = CreateWrapperT(Direct3D, *obp);
		}
		else
		{
			str << std::endl;
			str << "\tNOT WRAPPED";
		}
	}

	str << std::endl;
	str << tostr_HR(hr);

	if (obp)
	{
		str << " " << *obp;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

ULONG DirectDraw::AddRef()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	ULONG count = this->_original->AddRef();

	str << std::endl;
	str << "\t" << count;

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return count;
}

ULONG DirectDraw::Release()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	ULONG count = this->_original->Release();

	if (count == 0)
	{
		delete this;
	}

	str << std::endl;
	str << "\t" << count;

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return count;
}

HRESULT DirectDraw::Compact()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->Compact();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::CreateClipper(
	DWORD dwFlags,
	LPDIRECTDRAWCLIPPER FAR *lplpDDClipper,
	IUnknown FAR *pUnkOuter
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->CreateClipper(dwFlags, lplpDDClipper, pUnkOuter);

	if (SUCCEEDED(hr))
	{
		*lplpDDClipper = CreateWrapperT(DirectDrawClipper, *lplpDDClipper);
	}

	str << std::endl;
	str << tostr_HR(hr);

	if (lplpDDClipper)
	{
		str << " " << *lplpDDClipper;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::CreatePalette(
	DWORD dwFlags,
	LPPALETTEENTRY lpColorTable,
	LPDIRECTDRAWPALETTE FAR *lplpDDPalette,
	IUnknown FAR *pUnkOuter
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	STR_ENUM(dwFlags, DDPCAPS, 1BIT);
	STR_ENUM(dwFlags, DDPCAPS, 2BIT);
	STR_ENUM(dwFlags, DDPCAPS, 4BIT);
	STR_ENUM(dwFlags, DDPCAPS, 8BITENTRIES);
	STR_ENUM(dwFlags, DDPCAPS, 8BIT);
	STR_ENUM(dwFlags, DDPCAPS, ALLOW256);

	HRESULT hr = this->_original->CreatePalette(dwFlags, lpColorTable, lplpDDPalette, pUnkOuter);

	if (SUCCEEDED(hr))
	{
		*lplpDDPalette = CreateWrapperT(DirectDrawPalette, *lplpDDPalette);
	}

	str << std::endl;
	str << tostr_HR(hr);

	if (lplpDDPalette)
	{
		str << " " << *lplpDDPalette;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::CreateSurface(
	LPDDSURFACEDESC lpDDSurfaceDesc,
	LPDIRECTDRAWSURFACE FAR *lplpDDSurface,
	IUnknown FAR *pUnkOuter
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << tostr_DDSURFACEDESC(lpDDSurfaceDesc);

	/* @TheRedDaemon: removed modification, intention is to see what it normally does, or not?

	if (lpDDSurfaceDesc)
	{
		if (lpDDSurfaceDesc->ddsCaps.dwCaps &  DDSCAPS_ZBUFFER)
		{
			lpDDSurfaceDesc->dwWidth = GetSystemMetrics(SM_CXSCREEN);
			lpDDSurfaceDesc->dwHeight = GetSystemMetrics(SM_CYSCREEN);

			str << std::endl;
			str << "\tMODIFIED";
			str << tostr_DDSURFACEDESC(lpDDSurfaceDesc);
		}
	}

	*/

	HRESULT hr = this->_original->CreateSurface(lpDDSurfaceDesc, lplpDDSurface, pUnkOuter);

	if (SUCCEEDED(hr))
	{
		*lplpDDSurface = CreateWrapperT(DirectDrawSurface, *lplpDDSurface);
	}

	str << std::endl;
	str << tostr_HR(hr);

	if (lplpDDSurface)
	{
		str << " " << *lplpDDSurface;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::DuplicateSurface(
	LPDIRECTDRAWSURFACE lpDDSurface,
	LPDIRECTDRAWSURFACE FAR *lplpDupDDSurface
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDDSurface;

	if (IsWrapper(lpDDSurface))
	{
		lpDDSurface = static_cast<DirectDrawSurface*>(lpDDSurface)->_original;
	}

	HRESULT hr = this->_original->DuplicateSurface(lpDDSurface, lplpDupDDSurface);

	if (SUCCEEDED(hr))
	{
		*lplpDupDDSurface = CreateWrapperT(DirectDrawSurface, *lplpDupDDSurface);
	}

	str << std::endl;
	str << tostr_HR(hr);

	if (lplpDupDDSurface)
	{
		str << " " << *lplpDupDDSurface;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

static LPDDENUMMODESCALLBACK s_lpEnumModesCallback;

static HRESULT CALLBACK EnumModesCallback(LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext)
{
	std::ostringstream str;
	str << "\t" << lpContext;
	str << tostr_DDSURFACEDESC(lpDDSurfaceDesc);

	LogText(str.str());
	return s_lpEnumModesCallback(lpDDSurfaceDesc, lpContext);
}

HRESULT DirectDraw::EnumDisplayModes(
	DWORD dwFlags,
	LPDDSURFACEDESC lpDDSurfaceDesc,
	LPVOID lpContext,
	LPDDENUMMODESCALLBACK lpEnumModesCallback
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	LogText(str.str());

	s_lpEnumModesCallback = lpEnumModesCallback;

	HRESULT hr = this->_original->EnumDisplayModes(dwFlags, lpDDSurfaceDesc, lpContext, EnumModesCallback);

	std::ostringstream str2;
	str2 << std::endl;
	str2 << tostr_HR(hr);
	str2 << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str2.str());
	return hr;
}

HRESULT DirectDraw::EnumSurfaces(
	DWORD dwFlags,
	LPDDSURFACEDESC lpDDSD,
	LPVOID lpContext,
	LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->EnumSurfaces(dwFlags, lpDDSD, lpContext, lpEnumSurfacesCallback);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::FlipToGDISurface()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->FlipToGDISurface();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::GetCaps(
	LPDDCAPS lpDDDriverCaps,
	LPDDCAPS lpDDHELCaps
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetCaps(lpDDDriverCaps, lpDDHELCaps);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::GetDisplayMode(
	LPDDSURFACEDESC lpDDSurfaceDesc
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetDisplayMode(lpDDSurfaceDesc);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::GetFourCCCodes(
	LPDWORD lpNumCodes,
	LPDWORD lpCodes
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetFourCCCodes(lpNumCodes, lpCodes);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::GetGDISurface(
	LPDIRECTDRAWSURFACE FAR *lplpGDIDDSSurface
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetGDISurface(lplpGDIDDSSurface);

	if (SUCCEEDED(hr))
	{
		*lplpGDIDDSSurface = GetOrCreateWrapperT(DirectDrawSurface, *lplpGDIDDSSurface);
	}

	str << std::endl;
	str << tostr_HR(hr);

	if (lplpGDIDDSSurface)
	{
		str << " " << *lplpGDIDDSSurface;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::GetMonitorFrequency(
	LPDWORD lpdwFrequency
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetMonitorFrequency(lpdwFrequency);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::GetScanLine(
	LPDWORD lpdwScanLine
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetScanLine(lpdwScanLine);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::GetVerticalBlankStatus(
	LPBOOL lpbIsInVB
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetVerticalBlankStatus(lpbIsInVB);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::Initialize(
	GUID FAR *lpGUID
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << tostr_GUID(lpGUID);

	HRESULT hr = this->_original->Initialize(lpGUID);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::RestoreDisplayMode()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->RestoreDisplayMode();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::SetCooperativeLevel(
	HWND hWnd,
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << hWnd;

	STR_ENUM(dwFlags, DDSCL, FULLSCREEN);
	STR_ENUM(dwFlags, DDSCL, ALLOWREBOOT);
	STR_ENUM(dwFlags, DDSCL, NOWINDOWCHANGES);
	STR_ENUM(dwFlags, DDSCL, NORMAL);
	STR_ENUM(dwFlags, DDSCL, EXCLUSIVE);
	STR_ENUM(dwFlags, DDSCL, ALLOWMODEX);
	STR_ENUM(dwFlags, DDSCL, SETFOCUSWINDOW);
	STR_ENUM(dwFlags, DDSCL, SETDEVICEWINDOW);
	STR_ENUM(dwFlags, DDSCL, CREATEDEVICEWINDOW);

	HRESULT hr = this->_original->SetCooperativeLevel(hWnd, dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::SetDisplayMode(
	DWORD dwWidth,
	DWORD dwHeight,
	DWORD dwBPP
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << dwWidth << "x" << dwHeight << " " << dwBPP;

	/* @TheRedDaemon: removed modification, intention is to see what it normally does, or not?

	dwWidth = GetSystemMetrics(SM_CXSCREEN);
	dwHeight = GetSystemMetrics(SM_CYSCREEN);

	str << std::endl;
	str << "\tMODIFIED";
	str << " " << dwWidth << "x" << dwHeight << " " << dwBPP;
	
	*/

	HRESULT hr = this->_original->SetDisplayMode(dwWidth, dwHeight, dwBPP);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw::WaitForVerticalBlank(
	DWORD dwFlags,
	HANDLE hEvent
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	STR_ENUM(dwFlags, DDWAITVB, BLOCKBEGIN);
	STR_ENUM(dwFlags, DDWAITVB, BLOCKBEGINEVENT);
	STR_ENUM(dwFlags, DDWAITVB, BLOCKEND);

	HRESULT hr = this->_original->WaitForVerticalBlank(dwFlags, hEvent);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}
