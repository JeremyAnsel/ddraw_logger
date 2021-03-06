// Copyright (c) 2014 J�r�my Ansel
// Licensed under the MIT license. See LICENSE.txt

#pragma once

class Direct3DExecuteBuffer : public IDirect3DExecuteBuffer
{
public:
	Direct3DExecuteBuffer(IDirect3DExecuteBuffer* original);

	virtual ~Direct3DExecuteBuffer();

	/*** IUnknown methods ***/

	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj);

	STDMETHOD_(ULONG, AddRef)(THIS);

	STDMETHOD_(ULONG, Release)(THIS);

	/*** IDirect3DExecuteBuffer methods ***/

	STDMETHOD(Initialize)(THIS_ LPDIRECT3DDEVICE, LPD3DEXECUTEBUFFERDESC);

	STDMETHOD(Lock)(THIS_ LPD3DEXECUTEBUFFERDESC);

	STDMETHOD(Unlock)(THIS);

	STDMETHOD(SetExecuteData)(THIS_ LPD3DEXECUTEDATA);

	STDMETHOD(GetExecuteData)(THIS_ LPD3DEXECUTEDATA);

	STDMETHOD(Validate)(THIS_ LPDWORD, LPD3DVALIDATECALLBACK, LPVOID, DWORD);

	STDMETHOD(Optimize)(THIS_ DWORD);

	IDirect3DExecuteBuffer* _original;
};
