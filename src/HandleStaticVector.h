#pragma once
#include <StaticVector.h>
#include <cassert>

template <typename T, size_t MAX_SIZE>
class HandleStaticVector
{
public:
	HandleStaticVector()
	{
		for (int& i : handle_map)
		{
			i = -1;
		}
	}

	T& operator[](int handle)
	{
		assert((handle >= 0 && handle < elements.capacity()) && "Invalid handle value");
		int data_idx = handle_map[handle];
		return elements[data_idx];
	}

	int push_back(T& element)
	{
		assert(!elements.is_full() && "HandleStaticVector is full");
		int idx = elements.push_back(element);
		int handle = -1;

		for (int i = 0; i < elements.capacity(); i++)
		{
			if (handle_map[i] == -1)
			{
				handle_map[i] = idx;
				handle = i;
				break;
			}
		}

		assert(handle > -1 && "HandleStaticVector was not full, but no empty handle slot found!");
		return handle;
	}

	int push_back(T&& element)
	{
		assert(!elements.is_full() && "HandleStaticVector is full");
		int idx = elements.push_back(element);
		int handle = -1;

		for (int i = 0; i < elements.capacity(); i++)
		{
			if (handle_map[i] == -1)
			{
				handle_map[i] = idx;
				handle = i;
				break;
			}
		}

		assert(handle > -1 && "HandleStaticVector was not full, but no empty handle slot found!");
		return handle;
	}

	void erase(unsigned int handle)
	{
		assert(elements.size() > 0 && "HandleStaticVector is empty!");

		int data_idx = handle_map[handle];
		int last_idx = elements.size() - 1;
		assert(data_idx != -1 && "Trying to erase already deleted element");

		elements.erase(data_idx);
		handle_map[handle] = -1;

		if (data_idx < last_idx)
		{
			for (int& handle : handle_map)
			{
				if (handle == last_idx)
				{
					handle = data_idx;
					break;
				}
			}
		}
	}

	size_t size()
	{
		return elements.size();
	}

	T* data()
	{
		return elements.data();
	}

private:
	StaticVector<T, MAX_SIZE> elements;
	int handle_map[MAX_SIZE] = {};
};