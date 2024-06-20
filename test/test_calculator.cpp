#include <gtest/gtest.h>
#include "calculator.h"

TEST(CalculatorTests, AddTest) {
    Calculator calc;
    EXPECT_EQ(calc.add(1, 1), 2);
}

TEST(CalculatorTests, SubtractTest) {
    Calculator calc;
    EXPECT_EQ(calc.subtract(1, 1), 0);
}

TEST(CalculatorTests, MultiplyTest) {
    Calculator calc;
    EXPECT_EQ(calc.multiply(2, 3), 6);
}

TEST(CalculatorTests, DivideTest) {
    Calculator calc;
    EXPECT_EQ(calc.divide(6, 2), 3);
}

TEST(CalculatorTests, DivideByZeroTest) {
    Calculator calc;
    EXPECT_THROW(calc.divide(1, 0), std::invalid_argument);
}
