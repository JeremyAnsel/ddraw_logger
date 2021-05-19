// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#include "common.h"
#include "DirectDrawPalette.h"
#include "DirectDraw.h"

DirectDrawPalette::DirectDrawPalette(IDirectDrawPalette* original)
{
	this->_original = original;
}

DirectDrawPalette::~DirectDrawPalette()
{
	RemoveWrapper(this->_original);
}

HRESULT DirectDrawPalette::QueryInterface(
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

ULONG DirectDrawPalette::AddRef()
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

ULONG DirectDrawPalette::Release()
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

HRESULT DirectDrawPalette::GetCaps(
	LPDWORD lpdwCaps
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetCaps(lpdwCaps);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawPalette::GetEntries(
	DWORD dwFlags,
	DWORD dwBase,
	DWORD dwNumEntries,
	LPPALETTEENTRY lpEntries
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->GetEntries(dwFlags, dwBase, dwNumEntries, lpEntries);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawPalette::Initialize(
	LPDIRECTDRAW lpDD,
	DWORD dwFlags,
	LPPALETTEENTRY lpDDColorTable
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	if (IsWrapper(lpDD))
	{
		lpDD = static_cast<DirectDraw*>(lpDD)->_original;
	}

	HRESULT hr = this->_original->Initialize(lpDD, dwFlags, lpDDColorTable);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}

HRESULT DirectDrawPalette::SetEntries(
	DWORD dwFlags,
	DWORD dwStartingEntry,
	DWORD dwCount,
	LPPALETTEENTRY lpEntries
	)
{
	std::ostringstream str;
	str << this << " " << __FUNCTION__;

	HRESULT hr = this->_original->SetEntries(dwFlags, dwStartingEntry, dwCount, lpEntries);

	str << std::endl;
	str << tostr_HR(hr);

	str << std::endl << "\treturn to: " << _ReturnAddress();

	LogText(str.str());
	return hr;
}
