// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#pragma once

class DirectDrawPalette : public IDirectDrawPalette
{
public:
	DirectDrawPalette(IDirectDrawPalette* original);

	virtual ~DirectDrawPalette();

	/*** IUnknown methods ***/

	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj);

	STDMETHOD_(ULONG, AddRef) (THIS);

	STDMETHOD_(ULONG, Release) (THIS);

	/*** IDirectDrawPalette methods ***/

	STDMETHOD(GetCaps)(THIS_ LPDWORD);

	STDMETHOD(GetEntries)(THIS_ DWORD, DWORD, DWORD, LPPALETTEENTRY);

	STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, DWORD, LPPALETTEENTRY);

	STDMETHOD(SetEntries)(THIS_ DWORD, DWORD, DWORD, LPPALETTEENTRY);

	IDirectDrawPalette* _original;
};
