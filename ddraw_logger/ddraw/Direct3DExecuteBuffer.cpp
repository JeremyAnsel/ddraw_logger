// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#include "common.h"
#include "Direct3DExecuteBuffer.h"
#include "Direct3DDevice.h"

Direct3DExecuteBuffer::Direct3DExecuteBuffer(IDirect3DExecuteBuffer* original)
{
	this->_original = original;
}

Direct3DExecuteBuffer::~Direct3DExecuteBuffer()
{
	RemoveWrapper(this->_original);
}

HRESULT Direct3DExecuteBuffer::QueryInterface(
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

ULONG Direct3DExecuteBuffer::AddRef()
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

ULONG Direct3DExecuteBuffer::Release()
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

HRESULT Direct3DExecuteBuffer::Initialize(
	LPDIRECT3DDEVICE lpDirect3DDevice,
	LPD3DEXECUTEBUFFERDESC lpDesc
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	if (IsWrapper(lpDirect3DDevice))
	{
		lpDirect3DDevice = static_cast<Direct3DDevice*>(lpDirect3DDevice)->_original;
	}

	HRESULT hr = this->_original->Initialize(lpDirect3DDevice, lpDesc);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DExecuteBuffer::Lock(
	LPD3DEXECUTEBUFFERDESC lpDesc
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->Lock(lpDesc);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DExecuteBuffer::Unlock()
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->Unlock();

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DExecuteBuffer::SetExecuteData(
	LPD3DEXECUTEDATA lpData
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->SetExecuteData(lpData);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DExecuteBuffer::GetExecuteData(
	LPD3DEXECUTEDATA lpData
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetExecuteData(lpData);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DExecuteBuffer::Validate(
	LPDWORD lpdwOffset,
	LPD3DVALIDATECALLBACK lpFunc,
	LPVOID lpUserArg,
	DWORD dwReserved
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->Validate(lpdwOffset, lpFunc, lpUserArg, dwReserved);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT Direct3DExecuteBuffer::Optimize(DWORD dwFlags)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->Optimize(dwFlags);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}
