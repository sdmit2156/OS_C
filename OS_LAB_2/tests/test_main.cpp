#include "gtest/gtest.h"
#include "../src/main.h"

TEST(ArrayReplaceTest, ReplaceMinMaxWithAverage) {
    std::vector<int> input = { 1, 2, 3, 4, 5 };
    std::vector<int> result = run_main(input);

    // Здесь среднее = 3, min = 1, max = 5 → они заменяются на 3
    std::vector<int> expected = { 3, 2, 3, 4, 3 };
    EXPECT_EQ(result, expected);
}

TEST(ArrayReplaceTest, AllEqualElements) {
    std::vector<int> input = { 7, 7, 7 };
    std::vector<int> result = run_main(input);
    std::vector<int> expected = { 7, 7, 7 }; // не меняется
    EXPECT_EQ(result, expected);
}
