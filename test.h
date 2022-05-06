#pragma once

#include <iostream>

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
// template <typename Allocator>
// void inizialz_fwlist(ForwardList<int, Allocator>& list) {
// 	auto last = list.begin();
// 	for (int i = 0; i < 10; ++i)
// 		last = list.insert_after(last, i);
// }