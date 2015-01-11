// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#pragma once

bool IsWrapper(void* wrapper);
void* GetWrapper(void* original);
void AddWrapper(void* wrapper, void* original);
void RemoveWrapper(void* original);

template<class Wrap, class Orig>
Wrap* CreateWrapper(void* original)
{
	void* wrapper = new Wrap((Orig*)original);
	AddWrapper(wrapper, original);
	return (Wrap*)wrapper;
}

#define CreateWrapperT(T, original) CreateWrapper<T,I ## T>((original))

template<class Wrap, class Orig>
Wrap* GetOrCreateWrapper(void* original)
{
	void* wrapper = GetWrapper(original);

	if (wrapper)
	{
		return (Wrap*)wrapper;
	}
	else
	{
		return CreateWrapper<Wrap, Orig>(original);
	}
}

#define GetOrCreateWrapperT(T, original) GetOrCreateWrapper<T,I ## T>((original))
