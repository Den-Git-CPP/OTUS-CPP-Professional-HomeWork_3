#include <map>
#include <functional>
#include <iostream>

#include "allocator.h"
#include "fwlist.h"

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& pair) {
	os << pair.first << ' ' << pair.second;
	return os;
}
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
template <typename Container>
void print_cont(const Container& cont) {
	for (const auto& elem : cont)
		std::cout << elem << '\n';
}

int main() {
	std::map<int, int> std_map_std_alloc;
	inizialz_map(std_map_std_alloc);
	std::cout << "\nstd_map_std_alloc:\n";
	print_cont(std_map_std_alloc);

	std::map<int, int, std::less<int>, My_Allocator<std::pair<const int, int>, 10>> std_map_my_alloc;
	inizialz_map(std_map_my_alloc);
	std::cout << "\nstd_map_my_alloc:\n";
	print_cont(std_map_my_alloc);

	ForwardList<int> fwdlist_std_alloc;
	inizialz_fwlist(fwdlist_std_alloc);
	std::cout << "\nfwdlist_std_alloc:\n";
	print_cont(fwdlist_std_alloc);

	ForwardList<int, My_Allocator<int, 10>> fwdlist_my_alloc;
	inizialz_fwlist(fwdlist_my_alloc);
	std::cout << "\nfwdlist_my_alloc:\n";
	print_cont(fwdlist_my_alloc);

}
