#include "sort.h"

#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <gtest/gtest.h>

#define SIZE 5
//#define SIZE 10000

TEST(Random, Ascending)
{
    srandom(time(nullptr));
    std::array<int, SIZE> arr;
    std::generate(std::begin(arr), std::end(arr), &random);
    cse::sort(std::begin(arr), std::end(arr));
    EXPECT_TRUE(std::is_sorted(std::cbegin(arr), std::cend(arr)));
}

TEST(Random, Descending)
{
    srandom(time(nullptr));
    std::array<int, SIZE> arr;
    std::generate(std::begin(arr), std::end(arr), &random);
    cse::sort(std::begin(arr), std::end(arr), std::greater<>{});
    EXPECT_TRUE(std::is_sorted(std::crbegin(arr), std::crend(arr)));
}
