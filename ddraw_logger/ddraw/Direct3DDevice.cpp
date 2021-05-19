// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#include "common.h"
#include "Direct3DDevice.h"
#include "Direct3D.h"
#include "Direct3DViewport.h"
#include "Direct3DExecuteBuffer.h"
#include "Direct3DTexture.h"
#include "ExecuteBufferDumper.h"

Direct3DDevice::Direct3DDevice(IDirect3DDevice* original)
{
	this->_original = original;
}

Direct3DDevice::~Direct3DDevice()
{
	RemoveWrapper(this->_original);
}

HRESULT Direct3DDevice::QueryInterface(
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

ULONG Direct3DDevice::AddRef()
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

ULONG Direct3DDevice::Release()
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

HRESULT Direct3DDevice::Initialize(
	LPDIRECT3D lpd3d,
	LPGUID lpGUID,
	LPD3DDEVICEDESC lpd3ddvdesc
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	if (IsWrapper(lpd3d))
	{
		lpd3d = static_cast<Direct3D*>(lpd3d)->_original;
	}

	HRESULT hr = this->_original->Initialize(lpd3d, lpGUID, lpd3ddvdesc);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::GetCaps(
	LPD3DDEVICEDESC lpD3DHWDevDesc,
	LPD3DDEVICEDESC lpD3DHELDevDesc
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetCaps(lpD3DHWDevDesc, lpD3DHELDevDesc);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::SwapTextureHandles(
	LPDIRECT3DTEXTURE lpD3DTex1,
	LPDIRECT3DTEXTURE lpD3DTex2
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpD3DTex1;
	str << " " << lpD3DTex2;

	if (IsWrapper(lpD3DTex1))
	{
		lpD3DTex1 = static_cast<Direct3DTexture*>(lpD3DTex1)->_original;
	}

	if (IsWrapper(lpD3DTex2))
	{
		lpD3DTex2 = static_cast<Direct3DTexture*>(lpD3DTex2)->_original;
	}

	HRESULT hr = this->_original->SwapTextureHandles(lpD3DTex1, lpD3DTex2);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::CreateExecuteBuffer(
	LPD3DEXECUTEBUFFERDESC lpDesc,
	LPDIRECT3DEXECUTEBUFFER *lplpDirect3DExecuteBuffer,
	IUnknown *pUnkOuter
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->CreateExecuteBuffer(lpDesc, lplpDirect3DExecuteBuffer, pUnkOuter);

	if (SUCCEEDED(hr))
	{
		*lplpDirect3DExecuteBuffer = CreateWrapperT(Direct3DExecuteBuffer, *lplpDirect3DExecuteBuffer);
	}

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::GetStats(
	LPD3DSTATS lpD3DStats
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetStats(lpD3DStats);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::Execute(
	LPDIRECT3DEXECUTEBUFFER lpDirect3DExecuteBuffer,
	LPDIRECT3DVIEWPORT lpDirect3DViewport,
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDirect3DExecuteBuffer;
	str << " " << lpDirect3DViewport;

	STR_ENUM(dwFlags, D3DEXECUTE, CLIPPED);
	STR_ENUM(dwFlags, D3DEXECUTE, UNCLIPPED);

	if (IsWrapper(lpDirect3DExecuteBuffer))
	{
		lpDirect3DExecuteBuffer = static_cast<Direct3DExecuteBuffer*>(lpDirect3DExecuteBuffer)->_original;
	}

	if (IsWrapper(lpDirect3DViewport))
	{
		lpDirect3DViewport = static_cast<Direct3DViewport*>(lpDirect3DViewport)->_original;
	}

	if (lpDirect3DExecuteBuffer)
	{
		DumpExecuteBuffer(lpDirect3DExecuteBuffer);
	}

	HRESULT hr = this->_original->Execute(lpDirect3DExecuteBuffer, lpDirect3DViewport, dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::AddViewport(
	LPDIRECT3DVIEWPORT lpDirect3DViewport
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDirect3DViewport;

	if (IsWrapper(lpDirect3DViewport))
	{
		lpDirect3DViewport = ((Direct3DViewport*)lpDirect3DViewport)->_original;
	}

	HRESULT hr = this->_original->AddViewport(lpDirect3DViewport);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::DeleteViewport(
	LPDIRECT3DVIEWPORT lpDirect3DViewport
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDirect3DViewport;

	if (IsWrapper(lpDirect3DViewport))
	{
		lpDirect3DViewport = static_cast<Direct3DViewport*>(lpDirect3DViewport)->_original;
	}

	HRESULT hr = this->_original->DeleteViewport(lpDirect3DViewport);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::NextViewport(
	LPDIRECT3DVIEWPORT lpDirect3DViewport,
	LPDIRECT3DVIEWPORT *lplpDirect3DViewport,
	DWORD dwFlags
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDirect3DViewport;

	STR_ENUM(dwFlags, D3DNEXT, NEXT);
	STR_ENUM(dwFlags, D3DNEXT, HEAD);
	STR_ENUM(dwFlags, D3DNEXT, TAIL);

	if (IsWrapper(lpDirect3DViewport))
	{
		lpDirect3DViewport = static_cast<Direct3DViewport*>(lpDirect3DViewport)->_original;
	}

	HRESULT hr = this->_original->NextViewport(lpDirect3DViewport, lplpDirect3DViewport, dwFlags);

	if (SUCCEEDED(hr))
	{
		*lplpDirect3DViewport = GetOrCreateWrapperT(Direct3DViewport, *lplpDirect3DViewport);
	}

	str << std::endl;
	str << tostr_HR(hr);

	if (lplpDirect3DViewport)
	{
		str << " " << *lplpDirect3DViewport;
	}

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::Pick(
	LPDIRECT3DEXECUTEBUFFER lpDirect3DExecuteBuffer,
	LPDIRECT3DVIEWPORT lpDirect3DViewport,
	DWORD dwFlags,
	LPD3DRECT lpRect
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;
	str << " " << lpDirect3DExecuteBuffer;
	str << " " << lpDirect3DViewport;
	str << tostr_D3DRECT(lpRect);

	if (IsWrapper(lpDirect3DExecuteBuffer))
	{
		lpDirect3DExecuteBuffer = static_cast<Direct3DExecuteBuffer*>(lpDirect3DExecuteBuffer)->_original;
	}

	if (IsWrapper(lpDirect3DViewport))
	{
		lpDirect3DViewport = static_cast<Direct3DViewport*>(lpDirect3DViewport)->_original;
	}

	HRESULT hr = this->_original->Pick(lpDirect3DExecuteBuffer, lpDirect3DViewport, dwFlags, lpRect);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::GetPickRecords(
	LPDWORD lpCount,
	LPD3DPICKRECORD lpD3DPickRec
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetPickRecords(lpCount, lpD3DPickRec);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

static LPD3DENUMTEXTUREFORMATSCALLBACK s_lpEnumTextureFormatsCallback;

HRESULT CALLBACK EnumTextureFormatsCallback(
	LPDDSURFACEDESC lpDdsd,
	LPVOID lpUserArg
	)
{
	std::ostringstream str;
	str << "\t" << tostr_DDSURFACEDESC(lpDdsd);

	LogText(str.str());

	return s_lpEnumTextureFormatsCallback(lpDdsd, lpUserArg);
}

HRESULT Direct3DDevice::EnumTextureFormats(
	LPD3DENUMTEXTUREFORMATSCALLBACK lpd3dEnumTextureProc,
	LPVOID lpArg
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	LogText(str.str());

	s_lpEnumTextureFormatsCallback = lpd3dEnumTextureProc;

	HRESULT hr = this->_original->EnumTextureFormats(EnumTextureFormatsCallback, lpArg);

	std::ostringstream str2;
	str2 << std::endl;
	str2 << tostr_HR(hr);
	str2 << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str2.str());
	return hr;
}

HRESULT Direct3DDevice::CreateMatrix(
	LPD3DMATRIXHANDLE lpD3DMatHandle
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->CreateMatrix(lpD3DMatHandle);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::SetMatrix(
	D3DMATRIXHANDLE d3dMatHandle,
	LPD3DMATRIX lpD3DMatrix
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->SetMatrix(d3dMatHandle, lpD3DMatrix);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::GetMatrix(
	D3DMATRIXHANDLE d3dMatHandle,
	LPD3DMATRIX lpD3DMatrix
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetMatrix(d3dMatHandle, lpD3DMatrix);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::DeleteMatrix(
	D3DMATRIXHANDLE d3dMatHandle
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->DeleteMatrix(d3dMatHandle);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::BeginScene()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->BeginScene();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::EndScene()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->EndScene();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DDevice::GetDirect3D(
	LPDIRECT3D *lplpD3D
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetDirect3D(lplpD3D);

	if (SUCCEEDED(hr))
	{
		*lplpD3D = GetOrCreateWrapperT(Direct3D, *lplpD3D);
	}

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}
