#pragma once

#include <cstddef>
#include <cstdlib>
#include <utility>
#include <array>
#include <stdexcept>

#include <iostream>
#include "fwlist.h"

template <typename val_int>
val_int factorial(val_int number) {
	val_int fact = 1;
	for (val_int i = 2; i <= number; ++i)
		fact *= i;
	return fact;
}

template <typename Allocator>
void inizialz_map(std::map<int, int, std::less<int>, Allocator>& map) {
	for (int i = 0; i < 10; ++i)
		map.emplace(i, factorial(i));
}

template <typename Allocator>
void inizialz_fwlist(ForwardList<int, Allocator>& list) {
	auto last = list.begin();
	for (int i = 0; i < 10; ++i)
		last = list.insert_after(last, i);
}




template <typename T, std::size_t size>
class My_Allocator_Test {
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	My_Allocator_Test() {
		_data = reinterpret_cast<T*>(std::malloc(size * sizeof(T)));
		if (_data == nullptr) {
			throw std::bad_alloc();
		}
		_mem_map.fill(false);
	}

	~My_Allocator_Test() {
		std::free(_data);
	}

	template <typename U>
	struct rebind {
		using other = My_Allocator_Test<U, size>;
	};

	T* allocate(std::size_t n) {
		if (size - _allocated_size < n) {
			throw std::bad_alloc();
		}
		
		std::size_t from = 0, to = 0;
		for (std::size_t i = 0; i < size; ++i) {
			if (_mem_map[i])
				continue;
			std::size_t j = i + 1;
			for (; j < size && !_mem_map[j] && j - i + 1 <= n; ++j) {}
			if (j - i == n) {
				from = i;
				to = j;
				break;
			}
		}
		if (from == 0 && to == 0) {
			throw std::bad_alloc();
		}
		for (std::size_t i = from; i < to; ++i){
			_mem_map[i] = true;
		}
		_allocated_size += n;
		return _data + from;
	}

	void deallocate(T* p, std::size_t n) {
		std::size_t from = p - _data;

		for (std::size_t i = 0; i < n; ++i, ++p) {
			_mem_map[from + i] = false;
		}
		_allocated_size -= n;
	}

	template <typename U, typename... Args>
	void construct(U* p, Args&&... args) {
		new (p) U(std::forward<Args>(args)...);
	}

	void destroy(T* p) {
		p->~T();
	}

	T* _data = nullptr;
	std::size_t _allocated_size = 0;
	std::array<bool, size> _mem_map;
};
