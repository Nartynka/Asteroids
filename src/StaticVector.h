#pragma once
#include <cassert>
template <typename T, size_t i>

class StaticVector
{
public:
	T& operator[](int idx)
	{
		assert(idx <= data_size && "Array index out of bound, exiting");
		return data_array[idx];
	}

	size_t size()
	{
		return data_size;
	}

	int push_back(T element)
	{
		assert(data_size != max_capacity && "Data table is full");
		data_array[data_size++] = element;
		return data_size-1;
	}

	void insert(int idx, T element)
	{
		assert(data_size != max_capacity && "Data table is full");
		data_array[idx] = element;
		data_size++;
	}

	void erase(unsigned int idx)
	{
		assert(data_size != 0 && "Data table is empty");
		data_array[idx] = data_array[data_size - 1];
		data_size--;
	}

	T* data()
	{
		return &data_array[0];
	}

private:
	T data_array[i];
	size_t data_size = 0;
	size_t max_capacity = i;
};