#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include "test.h"

TEST(Template_Fuction, Factorial) { 
  EXPECT_EQ(factorial(0), 1);
  EXPECT_EQ(factorial(1), 1);
  EXPECT_EQ(factorial(2), 2);
  EXPECT_EQ(factorial(3), 6);
  EXPECT_EQ(factorial(4), 24);
  EXPECT_EQ(factorial(5), 120);
  EXPECT_EQ(factorial(6), 720);
  EXPECT_EQ(factorial(7), 5040);
  EXPECT_EQ(factorial(8), 40320);
  EXPECT_EQ(factorial(9), 362880);
 }

TEST(Template_Fuction, inizialz_map) { 
//arrange
  std::map<int, int> std_map_std_alloc;
//act
	inizialz_map(std_map_std_alloc);
//assert
EXPECT_EQ(std_map_std_alloc[0], 1);
EXPECT_EQ(std_map_std_alloc[5], 120);
EXPECT_EQ(std_map_std_alloc[9], 362880);
}

TEST(Template_Fuction, inizialz_fwlist) { 
//arrange
std::map<int, int, std::less<int>, My_Allocator_Test<std::pair<const int, int>, 10>> std_map_my_alloc;
//act
inizialz_map(std_map_my_alloc);
//assert
EXPECT_EQ(std_map_my_alloc[0], 1);
EXPECT_EQ(std_map_my_alloc[5], 120);
EXPECT_EQ(std_map_my_alloc[9], 362880);
}

TEST(My_Allocator, allocate) { 
const size_t size = 10;
My_Allocator_Test<int, size> allocator;
int* ptr=allocator.allocate(10);
ASSERT_TRUE(ptr != nullptr);
EXPECT_EQ(allocator._allocated_size,10);
}

TEST(My_Allocator, deallocate) { 
const size_t size = 10;
My_Allocator_Test<int, size> allocator;
int* ptr=allocator.allocate(10);
allocator.deallocate(ptr,10);
allocator.destroy(ptr);
EXPECT_EQ(allocator._allocated_size,0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

