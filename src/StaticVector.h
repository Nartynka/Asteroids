#pragma once
#include <cassert>
#include <utility>
#include <algorithm>


template <typename T, size_t i>
class StaticVector
{
public:
	T& operator[](int idx)
	{
		assert((idx >= 0 && idx < data_size) && "Index out of bound");
		return data_array[idx];
	}

	size_t size()
	{
		return data_size;
	}

	size_t capacity()
	{
		return max_capacity;
	}

	bool is_full()
	{
		return data_size == max_capacity;
	}

	int push_back(T& element)
	{
		assert(data_size < max_capacity && "Data array is full");
		data_array[data_size++] = std::move(element);
		return (int)data_size - 1;
	}

	int push_back(T&& element)
	{
		assert(data_size < max_capacity && "Data array is full");
		data_array[data_size++] = std::move(element);
		return (int)data_size - 1;
	}

	void erase(unsigned int idx)
	{
		assert(data_size > 0 && "Static Vector is empty!");
		assert((idx < data_size && idx >= 0) && "Index out of range");
		data_size--;
		if (idx < data_size)
		{
			data_array[idx] = data_array[data_size];
		}
	}

	T* data()
	{
		return &data_array[0];
	}

	void fill(T value)
	{
		for (T& e : data_array)
		{
			e = value;
		}
	}

	bool contains(T& element)
	{
		// Algorithms are "less error-prone than loops as they were already written and tested - a lot"
		// And std::find is more readable than a simple for loop
		// You can directly see that you are trying to *find* something there.
		//for (T& e : data_array)
		//{
		//	if (e == element)
		//		return true;
		//}
		//return false;

		T* result = std::find(std::begin(data_array), std::end(data_array), element);
		//return !result;

		if (result != std::end(data_array))
		{
			return true;
		}
		return false;
	}

private:
	T data_array[i] = {};
	size_t data_size = 0;
	size_t max_capacity = i;
};