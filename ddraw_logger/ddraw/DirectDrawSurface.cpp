// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#include "common.h"
#include "DirectDrawSurface.h"
#include "DirectDrawPalette.h"
#include "DirectDrawClipper.h"
#include "DirectDraw.h"
#include "Direct3DDevice.h"
#include "Direct3DTexture.h"

DirectDrawSurface::DirectDrawSurface(IDirectDrawSurface* original)
{
	this->_original = original;
}

DirectDrawSurface::~DirectDrawSurface()
{
	RemoveWrapper(this->_original);
}

HRESULT DirectDrawSurface::QueryInterface(
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
		else if (riid == IID_IDirect3DDevice || riid == IID_IDirect3DHALDevice || riid == IID_IDirect3DRGBDevice || riid == IID_IDirect3DRampDevice)
		{
			*obp = CreateWrapperT(Direct3DDevice, *obp);
		}
		else if (riid == IID_IDirect3DTexture)
		{
			*obp = CreateWrapperT(Direct3DTexture, *obp);
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

ULONG DirectDrawSurface::AddRef()
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

ULONG DirectDrawSurface::Release()
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

HRESULT DirectDrawSurface::AddAttachedSurface(
	LPDIRECTDRAWSURFACE lpDDSAttachedSurface
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDDSAttachedSurface;

	if (IsWrapper(lpDDSAttachedSurface))
	{
		lpDDSAttachedSurface = static_cast<DirectDrawSurface*>(lpDDSAttachedSurface)->_original;
	}

	HRESULT hr = this->_original->AddAttachedSurface(lpDDSAttachedSurface);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::AddOverlayDirtyRect(
	LPRECT lpRect
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;


	HRESULT hr = this->_original->AddOverlayDirtyRect(lpRect);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::Blt(
	LPRECT lpDestRect,
	LPDIRECTDRAWSURFACE lpDDSrcSurface,
	LPRECT lpSrcRect,
	DWORD dwFlags,
	LPDDBLTFX lpDDBltFx
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << tostr_RECT(lpDestRect);
	str << " " << lpDDSrcSurface;
	str << tostr_RECT(lpSrcRect);

	STR_ENUM(dwFlags, DDBLT, ALPHADEST);
	STR_ENUM(dwFlags, DDBLT, ALPHADESTCONSTOVERRIDE);
	STR_ENUM(dwFlags, DDBLT, ALPHADESTNEG);
	STR_ENUM(dwFlags, DDBLT, ALPHADESTSURFACEOVERRIDE);
	STR_ENUM(dwFlags, DDBLT, ALPHAEDGEBLEND);
	STR_ENUM(dwFlags, DDBLT, ALPHASRC);
	STR_ENUM(dwFlags, DDBLT, ALPHASRCCONSTOVERRIDE);
	STR_ENUM(dwFlags, DDBLT, ALPHASRCNEG);
	STR_ENUM(dwFlags, DDBLT, ALPHASRCSURFACEOVERRIDE);
	STR_ENUM(dwFlags, DDBLT, ASYNC);
	STR_ENUM(dwFlags, DDBLT, COLORFILL);
	STR_ENUM(dwFlags, DDBLT, DDFX);
	STR_ENUM(dwFlags, DDBLT, DDROPS);
	STR_ENUM(dwFlags, DDBLT, KEYDEST);
	STR_ENUM(dwFlags, DDBLT, KEYDESTOVERRIDE);
	STR_ENUM(dwFlags, DDBLT, KEYSRC);
	STR_ENUM(dwFlags, DDBLT, KEYSRCOVERRIDE);
	STR_ENUM(dwFlags, DDBLT, ROP);
	STR_ENUM(dwFlags, DDBLT, ROTATIONANGLE);
	STR_ENUM(dwFlags, DDBLT, ZBUFFER);
	STR_ENUM(dwFlags, DDBLT, ZBUFFERDESTCONSTOVERRIDE);
	STR_ENUM(dwFlags, DDBLT, ZBUFFERDESTOVERRIDE);
	STR_ENUM(dwFlags, DDBLT, ZBUFFERSRCCONSTOVERRIDE);
	STR_ENUM(dwFlags, DDBLT, ZBUFFERSRCOVERRIDE);
	STR_ENUM(dwFlags, DDBLT, WAIT);
	STR_ENUM(dwFlags, DDBLT, DEPTHFILL);
	STR_ENUM(dwFlags, DDBLT, DONOTWAIT);

	if (IsWrapper(lpDDSrcSurface))
	{
		lpDDSrcSurface = static_cast<DirectDrawSurface*>(lpDDSrcSurface)->_original;
	}

	DDBLTFX fx;

	if (lpDDBltFx)
	{
		fx = *lpDDBltFx;
		lpDDBltFx = &fx;

		if (dwFlags & DDBLT_ZBUFFERDESTOVERRIDE)
		{
			if (IsWrapper(fx.lpDDSZBufferDest))
			{
				fx.lpDDSZBufferDest = static_cast<DirectDrawSurface*>(fx.lpDDSZBufferDest)->_original;
			}
		}

		if (dwFlags & DDBLT_ZBUFFERSRCOVERRIDE)
		{
			if (IsWrapper(fx.lpDDSZBufferSrc))
			{
				fx.lpDDSZBufferSrc = static_cast<DirectDrawSurface*>(fx.lpDDSZBufferSrc)->_original;
			}
		}

		if (dwFlags & DDBLT_ALPHADESTSURFACEOVERRIDE)
		{
			if (IsWrapper(fx.lpDDSAlphaDest))
			{
				fx.lpDDSAlphaDest = static_cast<DirectDrawSurface*>(fx.lpDDSAlphaDest)->_original;
			}
		}

		if (dwFlags & DDBLT_ALPHASRCSURFACEOVERRIDE)
		{
			if (IsWrapper(fx.lpDDSAlphaSrc))
			{
				fx.lpDDSAlphaSrc = static_cast<DirectDrawSurface*>(fx.lpDDSAlphaSrc)->_original;
			}
		}

		// TODO: unwrap fx.lpDDSPattern
	}

	HRESULT hr = this->_original->Blt(lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::BltBatch(
	LPDDBLTBATCH lpDDBltBatch,
	DWORD dwCount,
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	str << std::endl;
	str << "\tNOT UNWRAPPED";

	HRESULT hr = this->_original->BltBatch(lpDDBltBatch, dwCount, dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::BltFast(
	DWORD dwX,
	DWORD dwY,
	LPDIRECTDRAWSURFACE lpDDSrcSurface,
	LPRECT lpSrcRect,
	DWORD dwTrans
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << dwX << "," << dwY;
	str << " " << lpDDSrcSurface;
	str << tostr_RECT(lpSrcRect);

	STR_ENUM(dwTrans, DDBLTFAST, NOCOLORKEY);
	STR_ENUM(dwTrans, DDBLTFAST, SRCCOLORKEY);
	STR_ENUM(dwTrans, DDBLTFAST, DESTCOLORKEY);
	STR_ENUM(dwTrans, DDBLTFAST, WAIT);
	STR_ENUM(dwTrans, DDBLTFAST, DONOTWAIT);

	if (IsWrapper(lpDDSrcSurface))
	{
		lpDDSrcSurface = static_cast<DirectDrawSurface*>(lpDDSrcSurface)->_original;
	}

	HRESULT hr = this->_original->BltFast(dwX, dwY, lpDDSrcSurface, lpSrcRect, dwTrans);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::DeleteAttachedSurface(
	DWORD dwFlags,
	LPDIRECTDRAWSURFACE lpDDSAttachedSurface
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDDSAttachedSurface;

	if (IsWrapper(lpDDSAttachedSurface))
	{
		lpDDSAttachedSurface = static_cast<DirectDrawSurface*>(lpDDSAttachedSurface)->_original;
	}

	HRESULT hr = this->_original->DeleteAttachedSurface(dwFlags, lpDDSAttachedSurface);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::EnumAttachedSurfaces(
	LPVOID lpContext,
	LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->EnumAttachedSurfaces(lpContext, lpEnumSurfacesCallback);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::EnumOverlayZOrders(
	DWORD dwFlags,
	LPVOID lpContext,
	LPDDENUMSURFACESCALLBACK lpfnCallback
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpContext;

	STR_ENUM(dwFlags, DDENUMOVERLAYZ, BACKTOFRONT);
	STR_ENUM(dwFlags, DDENUMOVERLAYZ, FRONTTOBACK);

	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->EnumOverlayZOrders(dwFlags, lpContext, lpfnCallback);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::Flip(
	LPDIRECTDRAWSURFACE lpDDSurfaceTargetOverride,
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDDSurfaceTargetOverride;

	STR_ENUM(dwFlags, DDFLIP, WAIT);
	STR_ENUM(dwFlags, DDFLIP, EVEN);
	STR_ENUM(dwFlags, DDFLIP, ODD);

	if (IsWrapper(lpDDSurfaceTargetOverride))
	{
		lpDDSurfaceTargetOverride = static_cast<DirectDrawSurface*>(lpDDSurfaceTargetOverride)->_original;
	}

	HRESULT hr = this->_original->Flip(lpDDSurfaceTargetOverride, dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::GetAttachedSurface(
	LPDDSCAPS lpDDSCaps,
	LPDIRECTDRAWSURFACE FAR *lplpDDAttachedSurface
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	if (lpDDSCaps)
	{
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, ALPHA);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, BACKBUFFER);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, COMPLEX);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, FLIP);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, FRONTBUFFER);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, OFFSCREENPLAIN);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, OVERLAY);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, PALETTE);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, PRIMARYSURFACE);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, PRIMARYSURFACELEFT);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, SYSTEMMEMORY);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, TEXTURE);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, 3DDEVICE);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, VIDEOMEMORY);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, VISIBLE);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, WRITEONLY);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, ZBUFFER);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, OWNDC);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, LIVEVIDEO);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, HWCODEC);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, MODEX);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, MIPMAP);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, ALLOCONLOAD);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, VIDEOPORT);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, LOCALVIDMEM);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, NONLOCALVIDMEM);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, STANDARDVGAMODE);
		STR_ENUM(lpDDSCaps->dwCaps, DDSCAPS, OPTIMIZED);
	}

	HRESULT hr = this->_original->GetAttachedSurface(lpDDSCaps, lplpDDAttachedSurface);

	if (SUCCEEDED(hr))
	{
		*lplpDDAttachedSurface = GetOrCreateWrapperT(DirectDrawSurface, *lplpDDAttachedSurface);
	}

	str << std::endl;
	str << tostr_HR(hr);

	if (lplpDDAttachedSurface)
	{
		str << " " << *lplpDDAttachedSurface;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::GetBltStatus(
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	STR_ENUM(dwFlags, DDGBS, CANBLT);
	STR_ENUM(dwFlags, DDGBS, ISBLTDONE);

	HRESULT hr = this->_original->GetBltStatus(dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::GetCaps(
	LPDDSCAPS lpDDSCaps
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetCaps(lpDDSCaps);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::GetClipper(
	LPDIRECTDRAWCLIPPER FAR *lplpDDClipper
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetClipper(lplpDDClipper);

	if (SUCCEEDED(hr))
	{
		*lplpDDClipper = GetOrCreateWrapperT(DirectDrawClipper, *lplpDDClipper);
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

HRESULT DirectDrawSurface::GetColorKey(
	DWORD dwFlags,
	LPDDCOLORKEY lpDDColorKey
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	STR_ENUM(dwFlags, DDCKEY, DESTBLT);
	STR_ENUM(dwFlags, DDCKEY, DESTOVERLAY);
	STR_ENUM(dwFlags, DDCKEY, SRCBLT);
	STR_ENUM(dwFlags, DDCKEY, SRCOVERLAY);

	HRESULT hr = this->_original->GetColorKey(dwFlags, lpDDColorKey);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::GetDC(
	HDC FAR *lphDC
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetDC(lphDC);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::GetFlipStatus(
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	STR_ENUM(dwFlags, DDGFS, CANFLIP);
	STR_ENUM(dwFlags, DDGFS, ISFLIPDONE);

	HRESULT hr = this->_original->GetFlipStatus(dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::GetOverlayPosition(
	LPLONG lplX,
	LPLONG lplY
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetOverlayPosition(lplX, lplY);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::GetPalette(
	LPDIRECTDRAWPALETTE FAR *lplpDDPalette
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetPalette(lplpDDPalette);

	if (SUCCEEDED(hr))
	{
		*lplpDDPalette = GetOrCreateWrapperT(DirectDrawPalette, *lplpDDPalette);
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

HRESULT DirectDrawSurface::GetPixelFormat(
	LPDDPIXELFORMAT lpDDPixelFormat
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetPixelFormat(lpDDPixelFormat);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::GetSurfaceDesc(
	LPDDSURFACEDESC lpDDSurfaceDesc
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetSurfaceDesc(lpDDSurfaceDesc);

	str << std::endl;
	str << tostr_HR(hr);

	if (SUCCEEDED(hr))
	{
		str << tostr_DDSURFACEDESC(lpDDSurfaceDesc);
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::Initialize(
	LPDIRECTDRAW lpDD,
	LPDDSURFACEDESC lpDDSurfaceDesc
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	if (IsWrapper(lpDD))
	{
		lpDD = static_cast<DirectDraw*>(lpDD)->_original;
	}

	HRESULT hr = this->_original->Initialize(lpDD, lpDDSurfaceDesc);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::IsLost()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->IsLost();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::Lock(
	LPRECT lpDestRect,
	LPDDSURFACEDESC lpDDSurfaceDesc,
	DWORD dwFlags,
	HANDLE hEvent
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << tostr_RECT(lpDestRect);

	STR_ENUM(dwFlags, DDLOCK, WAIT);
	STR_ENUM(dwFlags, DDLOCK, EVENT);
	STR_ENUM(dwFlags, DDLOCK, READONLY);
	STR_ENUM(dwFlags, DDLOCK, WRITEONLY);
	STR_ENUM(dwFlags, DDLOCK, NOSYSLOCK);

	HRESULT hr = this->_original->Lock(lpDestRect, lpDDSurfaceDesc, dwFlags, hEvent);

	str << std::endl;
	str << tostr_HR(hr);

	if (SUCCEEDED(hr))
	{
		str << tostr_DDSURFACEDESC(lpDDSurfaceDesc);
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::ReleaseDC(
	HDC hDC
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->ReleaseDC(hDC);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::Restore()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->Restore();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::SetClipper(
	LPDIRECTDRAWCLIPPER lpDDClipper
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDDClipper;

	if (IsWrapper(lpDDClipper))
	{
		lpDDClipper = static_cast<DirectDrawClipper*>(lpDDClipper)->_original;
	}

	HRESULT hr = this->_original->SetClipper(lpDDClipper);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::SetColorKey(
	DWORD dwFlags,
	LPDDCOLORKEY lpDDColorKey
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	STR_ENUM(dwFlags, DDCKEY, COLORSPACE);
	STR_ENUM(dwFlags, DDCKEY, DESTBLT);
	STR_ENUM(dwFlags, DDCKEY, DESTOVERLAY);
	STR_ENUM(dwFlags, DDCKEY, SRCBLT);
	STR_ENUM(dwFlags, DDCKEY, SRCOVERLAY);

	HRESULT hr = this->_original->SetColorKey(dwFlags, lpDDColorKey);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::SetOverlayPosition(
	LONG lX,
	LONG lY
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->SetOverlayPosition(lX, lY);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::SetPalette(
	LPDIRECTDRAWPALETTE lpDDPalette
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	if (IsWrapper(lpDDPalette))
	{
		lpDDPalette = static_cast<DirectDrawPalette*>(lpDDPalette)->_original;
	}

	HRESULT hr = this->_original->SetPalette(lpDDPalette);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::Unlock(
	LPVOID lpSurfaceData
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->Unlock(lpSurfaceData);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::UpdateOverlay(
	LPRECT lpSrcRect,
	LPDIRECTDRAWSURFACE lpDDDestSurface,
	LPRECT lpDestRect,
	DWORD dwFlags,
	LPDDOVERLAYFX lpDDOverlayFx
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << tostr_RECT(lpSrcRect);
	str << " " << lpDDDestSurface;
	str << tostr_RECT(lpDestRect);

	if (IsWrapper(lpDDDestSurface))
	{
		lpDDDestSurface = static_cast<DirectDrawSurface*>(lpDDDestSurface)->_original;
	}

	DDOVERLAYFX fx;

	if (lpDDOverlayFx)
	{
		fx = *lpDDOverlayFx;
		lpDDOverlayFx = &fx;

		if (dwFlags & DDOVER_ALPHADESTSURFACEOVERRIDE)
		{
			if (IsWrapper(fx.lpDDSAlphaDest))
			{
				fx.lpDDSAlphaDest = static_cast<DirectDrawSurface*>(fx.lpDDSAlphaDest)->_original;
			}
		}

		if (dwFlags & DDOVER_ALPHASRCSURFACEOVERRIDE)
		{
			if (IsWrapper(fx.lpDDSAlphaSrc))
			{
				fx.lpDDSAlphaSrc = static_cast<DirectDrawSurface*>(fx.lpDDSAlphaSrc)->_original;
			}
		}
	}

	HRESULT hr = this->_original->UpdateOverlay(lpSrcRect, lpDDDestSurface, lpDestRect, dwFlags, lpDDOverlayFx);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::UpdateOverlayDisplay(
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	STR_ENUM(dwFlags, DDOVER, REFRESHDIRTYRECTS);
	STR_ENUM(dwFlags, DDOVER, REFRESHALL);

	HRESULT hr = this->_original->UpdateOverlayDisplay(dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawSurface::UpdateOverlayZOrder(
	DWORD dwFlags,
	LPDIRECTDRAWSURFACE lpDDSReference
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	switch (dwFlags)
	{
	case DDOVERZ_SENDTOFRONT:
		str << " SENDTOFRONT";
		break;

	case DDOVERZ_SENDTOBACK:
		str << " SENDTOBACK";
		break;

	case DDOVERZ_MOVEFORWARD:
		str << " MOVEFORWARD";
		break;

	case DDOVERZ_MOVEBACKWARD:
		str << " MOVEBACKWARD";
		break;

	case DDOVERZ_INSERTINFRONTOF:
		str << " INSERTINFRONTOF";
		break;

	case DDOVERZ_INSERTINBACKOF:
		str << " INSERTINBACKOF";
		break;
	}

	str << " " << lpDDSReference;

	if (IsWrapper(lpDDSReference))
	{
		lpDDSReference = static_cast<DirectDrawSurface*>(lpDDSReference)->_original;
	}

	HRESULT hr = this->_original->UpdateOverlayZOrder(dwFlags, lpDDSReference);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}
