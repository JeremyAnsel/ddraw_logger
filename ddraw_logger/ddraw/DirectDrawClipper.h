#pragma once

class DirectDrawClipper : public IDirectDrawClipper
{
public:
	DirectDrawClipper(IDirectDrawClipper* original);

	virtual ~DirectDrawClipper();

	/*** IUnknown methods ***/

	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj);

	STDMETHOD_(ULONG, AddRef) (THIS);

	STDMETHOD_(ULONG, Release) (THIS);

	/*** IDirectDrawClipper methods ***/

	STDMETHOD(GetClipList)(THIS_ LPRECT, LPRGNDATA, LPDWORD);

	STDMETHOD(GetHWnd)(THIS_ HWND FAR *);

	STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, DWORD);

	STDMETHOD(IsClipListChanged)(THIS_ BOOL FAR *);

	STDMETHOD(SetClipList)(THIS_ LPRGNDATA, DWORD);

	STDMETHOD(SetHWnd)(THIS_ DWORD, HWND);

	IDirectDrawClipper* _original;
};
