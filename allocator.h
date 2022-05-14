#pragma once
/*
#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif
*/
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <array>
#include <stdexcept>


//#define USE_PRETTY 1

template <typename T, std::size_t size>
class My_Allocator {
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	My_Allocator() =default;

	~My_Allocator() {
		std::free(_data);
	}

	template <typename U>
	struct rebind {
		using other = My_Allocator<U, size>;
	};

	T* allocate(std::size_t n) {
		/*
		#ifndef USE_PRETTY
				std::cout << "allocate: [n = " << n << "]" << std::endl;
		#else
				std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		#endif
		*/
		_data = reinterpret_cast<T*>(std::malloc(size * sizeof(T)));
		if (_data == nullptr) {
			throw std::bad_alloc();
		}
		_mem_map.fill(false);

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
		/*
		#ifndef USE_PRETTY
				std::cout << "deallocate: [n  = " << n << "] " << std::endl;
		#else
				std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		#endif
		*/
		std::size_t from = p - _data;

		for (std::size_t i = 0; i < n; ++i, ++p) {
			_mem_map[from + i] = false;
		}
		_allocated_size -= n;
	}

	template <typename U, typename... Args>
	void construct(U* p, Args&&... args) {
		/*
		#ifndef USE_PRETTY
				std::cout << "construct" << std::endl;
		#else
				std::cout << __PRETTY_FUNCTION__ << std::endl;
		#endif
		*/
		new (p) U(std::forward<Args>(args)...);
	}

	void destroy(T* p) {
		/*
		#ifndef USE_PRETTY
				std::cout << "destroy" << std::endl;
		#else
				std::cout << __PRETTY_FUNCTION__ << std::endl;
		#endif
		*/
		p->~T();
	}

private:
	T* _data = nullptr;
	std::size_t _allocated_size = 0;
	std::array<bool, size> _mem_map;
};
