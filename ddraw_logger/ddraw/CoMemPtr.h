// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#pragma once

template<class T>
class CoMemPtr
{
private:
	T* _ptr;

public:
	CoMemPtr()
	{
		this->_ptr = nullptr;
	}

	CoMemPtr(T* ptr)
	{
		this->_ptr = ptr;
	}

	~CoMemPtr()
	{
		this->Free();
	}

	operator T*()
	{
		return this->_ptr;
	}

	operator bool()
	{
		return this->_ptr != nullptr;
	}

	T** operator &()
	{
		this->Free();
		return &this->_ptr;
	}

	void Free()
	{
		if (this->_ptr != nullptr)
		{
			CoTaskMemFree(this->_ptr);
		}
	}

	T* Get()
	{
		return this->_ptr;
	}

	T** GetAddressOf()
	{
		return &this->_ptr;
	}
};
