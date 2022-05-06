#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include "test.h"

//#include "allocator.h"
//#include "fwlist.h"

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


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

