// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#include "common.h"
#include "Direct3DTexture.h"
#include "Direct3DDevice.h"
#include "DirectDrawSurface.h"

Direct3DTexture::Direct3DTexture(IDirect3DTexture* original)
{
	this->_original = original;
}

Direct3DTexture::~Direct3DTexture()
{
	RemoveWrapper(this->_original);
}

HRESULT Direct3DTexture::QueryInterface(
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

ULONG Direct3DTexture::AddRef()
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

ULONG Direct3DTexture::Release()
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

HRESULT Direct3DTexture::Initialize(LPDIRECT3DDEVICE lpD3DDevice, LPDIRECTDRAWSURFACE lpD3DSurface)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	if (IsWrapper(lpD3DDevice))
	{
		lpD3DDevice = static_cast<Direct3DDevice*>(lpD3DDevice)->_original;
	}

	if (IsWrapper(lpD3DSurface))
	{
		lpD3DSurface = static_cast<DirectDrawSurface*>(lpD3DSurface)->_original;
	}

	HRESULT hr = this->_original->Initialize(lpD3DDevice, lpD3DSurface);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DTexture::GetHandle(
	LPDIRECT3DDEVICE lpDirect3DDevice,
	LPD3DTEXTUREHANDLE lpHandle
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpHandle;

	if (IsWrapper(lpDirect3DDevice))
	{
		lpDirect3DDevice = static_cast<Direct3DDevice*>(lpDirect3DDevice)->_original;
	}

	HRESULT hr = this->_original->GetHandle(lpDirect3DDevice, lpHandle);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DTexture::PaletteChanged(
	DWORD dwStart,
	DWORD dwCount
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->PaletteChanged(dwStart, dwCount);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DTexture::Load(
	LPDIRECT3DTEXTURE lpD3DTexture
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpD3DTexture;

	if (IsWrapper(lpD3DTexture))
	{
		lpD3DTexture = static_cast<Direct3DTexture*>(lpD3DTexture)->_original;
	}

	HRESULT hr = this->_original->Load(lpD3DTexture);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DTexture::Unload()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->Unload();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}
