// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#include "common.h"
#include "Direct3D.h"
#include "Direct3DViewport.h"

Direct3D::Direct3D(IDirect3D* original)
{
	this->_original = original;
}

Direct3D::~Direct3D()
{
	RemoveWrapper(this->_original);
}

HRESULT Direct3D::QueryInterface(
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

ULONG Direct3D::AddRef()
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

ULONG Direct3D::Release()
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

HRESULT Direct3D::Initialize(REFCLSID riid)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->Initialize(riid);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

static LPD3DENUMDEVICESCALLBACK s_lpEnumDevicesCallback;

static HRESULT CALLBACK EnumDevicesCallback(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC lpD3DHWDeviceDesc, LPD3DDEVICEDESC lpD3DHELDeviceDesc, LPVOID lpContext)
{
	std::ostringstream str;
	str << "\t" << lpDeviceName << "\t" << lpDeviceDescription;

	LogText(str.str());

	return s_lpEnumDevicesCallback(lpGuid, lpDeviceDescription, lpDeviceName, lpD3DHWDeviceDesc, lpD3DHELDeviceDesc, lpContext);
}

HRESULT Direct3D::EnumDevices(
	LPD3DENUMDEVICESCALLBACK lpEnumDevicesCallback,
	LPVOID lpUserArg
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	LogText(str.str());

	s_lpEnumDevicesCallback = lpEnumDevicesCallback;

	HRESULT hr = this->_original->EnumDevices(EnumDevicesCallback, lpUserArg);

	std::ostringstream str2;
	str2 << std::endl;
	str2 << tostr_HR(hr);
	str2 << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str2.str());
	return hr;
}

HRESULT Direct3D::CreateLight(
	LPDIRECT3DLIGHT* lplpDirect3DLight,
	IUnknown* pUnkOuter
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->CreateLight(lplpDirect3DLight, pUnkOuter);

	str << std::endl;
	str << tostr_HR(hr);

	if (lplpDirect3DLight)
	{
		str << " " << *lplpDirect3DLight;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3D::CreateMaterial(
	LPDIRECT3DMATERIAL* lplpDirect3DMaterial,
	IUnknown* pUnkOuter
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	str << std::endl;
	str << "\tNOT WRAPPED";

	HRESULT hr = this->_original->CreateMaterial(lplpDirect3DMaterial, pUnkOuter);

	str << std::endl;
	str << tostr_HR(hr);

	if (lplpDirect3DMaterial)
	{
		str << " " << *lplpDirect3DMaterial;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3D::CreateViewport(
	LPDIRECT3DVIEWPORT* lplpD3DViewport,
	IUnknown* pUnkOuter
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->CreateViewport(lplpD3DViewport, pUnkOuter);

	if (SUCCEEDED(hr))
	{
		*lplpD3DViewport = CreateWrapperT(Direct3DViewport, *lplpD3DViewport);
	}

	str << std::endl;
	str << tostr_HR(hr);

	if (lplpD3DViewport)
	{
		str << " " << *lplpD3DViewport;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3D::FindDevice(
	LPD3DFINDDEVICESEARCH lpD3DFDS,
	LPD3DFINDDEVICERESULT lpD3DFDR
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	LogText(str.str());

	HRESULT hr = this->_original->FindDevice(lpD3DFDS, lpD3DFDR);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}
