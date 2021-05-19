// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#include "common.h"
#include "DirectDraw4.h"
#include "DirectDrawClipper.h"
#include "DirectDrawPalette.h"

DirectDraw4::DirectDraw4(IDirectDraw4* original)
{
	this->_original = original;
}

DirectDraw4::~DirectDraw4()
{
	RemoveWrapper(this->_original);
}

HRESULT DirectDraw4::QueryInterface(
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

ULONG DirectDraw4::AddRef()
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

ULONG DirectDraw4::Release()
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

HRESULT DirectDraw4::Compact()
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

HRESULT DirectDraw4::CreateClipper(
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

HRESULT DirectDraw4::CreatePalette(
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

HRESULT DirectDraw4::CreateSurface(
	LPDDSURFACEDESC2 lpDDSurfaceDesc,
	LPDIRECTDRAWSURFACE4 FAR *lplpDDSurface,
	IUnknown FAR *pUnkOuter
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->CreateSurface(lpDDSurfaceDesc, lplpDDSurface, pUnkOuter);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw4::DuplicateSurface(
	LPDIRECTDRAWSURFACE4 lpDDSurface,
	LPDIRECTDRAWSURFACE4 FAR *lplpDupDDSurface
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDDSurface;

	str << std::endl;
	str << "\tNOT UWRAPPED";
	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->DuplicateSurface(lpDDSurface, lplpDupDDSurface);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw4::EnumDisplayModes(
	DWORD dwFlags,
	LPDDSURFACEDESC2 lpDDSurfaceDesc,
	LPVOID lpContext,
	LPDDENUMMODESCALLBACK2 lpEnumModesCallback
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->EnumDisplayModes(dwFlags, lpDDSurfaceDesc, lpContext, lpEnumModesCallback);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

// @TheRedDaemon: No log for callback function here?
HRESULT DirectDraw4::EnumSurfaces(
	DWORD dwFlags,
	LPDDSURFACEDESC2 lpDDSD,
	LPVOID lpContext,
	LPDDENUMSURFACESCALLBACK2 lpEnumSurfacesCallback
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

HRESULT DirectDraw4::FlipToGDISurface()
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

HRESULT DirectDraw4::GetCaps(
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

HRESULT DirectDraw4::GetDisplayMode(
	LPDDSURFACEDESC2 lpDDSurfaceDesc
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

HRESULT DirectDraw4::GetFourCCCodes(
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

HRESULT DirectDraw4::GetGDISurface(
	LPDIRECTDRAWSURFACE4 FAR *lplpGDIDDSSurface
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->GetGDISurface(lplpGDIDDSSurface);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw4::GetMonitorFrequency(
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

HRESULT DirectDraw4::GetScanLine(
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

HRESULT DirectDraw4::GetVerticalBlankStatus(
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

HRESULT DirectDraw4::Initialize(
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

HRESULT DirectDraw4::RestoreDisplayMode()
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

HRESULT DirectDraw4::SetCooperativeLevel(
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

HRESULT DirectDraw4::SetDisplayMode(
	DWORD dwWidth,
	DWORD dwHeight,
	DWORD dwBPP,
	DWORD dwRefreshRate,
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << dwWidth << "x" << dwHeight << " " << dwBPP << " " << dwRefreshRate;

	HRESULT hr = this->_original->SetDisplayMode(dwWidth, dwHeight, dwBPP, dwRefreshRate, dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw4::WaitForVerticalBlank(
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

HRESULT DirectDraw4::GetAvailableVidMem(
	LPDDSCAPS2 lpDDSCaps,
	LPDWORD lpdwTotal,
	LPDWORD lpdwFree
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetAvailableVidMem(lpDDSCaps, lpdwTotal, lpdwFree);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw4::GetSurfaceFromDC(
	HDC hdc,
	LPDIRECTDRAWSURFACE4 * lpDDS4
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->GetSurfaceFromDC(hdc, lpDDS4);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw4::RestoreAllSurfaces()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->RestoreAllSurfaces();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw4::TestCooperativeLevel()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->TestCooperativeLevel();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDraw4::GetDeviceIdentifier(
	LPDDDEVICEIDENTIFIER lpdddi,
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetDeviceIdentifier(lpdddi, dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}
