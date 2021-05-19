// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#include "common.h"
#include "Direct3DViewport.h"
#include "Direct3D.h"
#include "DirectDrawSurface.h"

Direct3DViewport::Direct3DViewport(IDirect3DViewport* original)
{
	this->_original = original;
}

Direct3DViewport::~Direct3DViewport()
{
	RemoveWrapper(this->_original);
}

HRESULT Direct3DViewport::QueryInterface(
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

ULONG Direct3DViewport::AddRef()
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

ULONG Direct3DViewport::Release()
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

HRESULT Direct3DViewport::Initialize(
	LPDIRECT3D lpDirect3D
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	if (IsWrapper(lpDirect3D))
	{
		lpDirect3D = static_cast<Direct3D*>(lpDirect3D)->_original;
	}

	HRESULT hr = this->_original->Initialize(lpDirect3D);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::GetViewport(
	LPD3DVIEWPORT lpData
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetViewport(lpData);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::SetViewport(
	LPD3DVIEWPORT lpData
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->SetViewport(lpData);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::TransformVertices(
	DWORD dwVertexCount,
	LPD3DTRANSFORMDATA lpData,
	DWORD dwFlags,
	LPDWORD lpOffscreen
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->TransformVertices(dwVertexCount, lpData, dwFlags, lpOffscreen);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::LightElements(
	DWORD dwElementCount,
	LPD3DLIGHTDATA lpData
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->LightElements(dwElementCount, lpData);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::SetBackground(
	D3DMATERIALHANDLE hMat
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->SetBackground(hMat);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::GetBackground(
	LPD3DMATERIALHANDLE lphMat,
	LPBOOL lpValid
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetBackground(lphMat, lpValid);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::SetBackgroundDepth(
	LPDIRECTDRAWSURFACE lpDDSurface
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDDSurface;

	if (IsWrapper(lpDDSurface))
	{
		lpDDSurface = static_cast<DirectDrawSurface*>(lpDDSurface)->_original;
	}

	HRESULT hr = this->_original->SetBackgroundDepth(lpDDSurface);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::GetBackgroundDepth(
	LPDIRECTDRAWSURFACE* lplpDDSurface,
	LPBOOL lpValid
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetBackgroundDepth(lplpDDSurface, lpValid);

	if (SUCCEEDED(hr))
	{
		*lplpDDSurface = GetOrCreateWrapperT(DirectDrawSurface, *lplpDDSurface);
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

HRESULT Direct3DViewport::Clear(
	DWORD dwCount,
	LPD3DRECT lpRects,
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	STR_ENUM(dwFlags, D3DCLEAR, TARGET);
	STR_ENUM(dwFlags, D3DCLEAR, ZBUFFER);

	HRESULT hr = this->_original->Clear(dwCount, lpRects, dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::AddLight(
	LPDIRECT3DLIGHT lpDirect3DLight
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDirect3DLight;

	str << std::endl;
	str << "\tNOT UNWRAPPED";

	HRESULT hr = this->_original->AddLight(lpDirect3DLight);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::DeleteLight(
	LPDIRECT3DLIGHT lpDirect3DLight
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDirect3DLight;

	LogText(str.str());

	str << std::endl;
	str << "\tNOT UNWRAPPED";

	HRESULT hr = this->_original->DeleteLight(lpDirect3DLight);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::NextLight(
	LPDIRECT3DLIGHT lpDirect3DLight,
	LPDIRECT3DLIGHT* lplpDirect3DLight,
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDirect3DLight;

	STR_ENUM(dwFlags, D3DNEXT, NEXT);
	STR_ENUM(dwFlags, D3DNEXT, HEAD);
	STR_ENUM(dwFlags, D3DNEXT, TAIL);

	str << std::endl;
	str << "\tNOT UNWRAPPED";
	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->NextLight(lpDirect3DLight, lplpDirect3DLight, dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::GetViewport2(
	LPD3DVIEWPORT2 lpData
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = E_NOTIMPL;

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::SetViewport2(
	LPD3DVIEWPORT2 lpData
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = E_NOTIMPL;

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::SetBackgroundDepth2(
	LPDIRECTDRAWSURFACE4 lpDDS
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = E_NOTIMPL;

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::GetBackgroundDepth2(
	LPDIRECTDRAWSURFACE4* lplpDDS,
	LPBOOL lpValid
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = E_NOTIMPL;

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DViewport::Clear2(
	DWORD     dwCount,
	LPD3DRECT lpRects,
	DWORD     dwFlags,
	DWORD     dwColor,
	D3DVALUE  dvZ,
	DWORD     dwStencil
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	STR_ENUM(dwFlags, D3DCLEAR, TARGET);
	STR_ENUM(dwFlags, D3DCLEAR, ZBUFFER);
	STR_ENUM(dwFlags, D3DCLEAR, STENCIL);

	HRESULT hr = ((LPDIRECT3DVIEWPORT3)this->_original)->Clear2(dwCount, lpRects, dwFlags, dwColor, dvZ, dwStencil);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}
