#include <gtest/gtest.h>

int suma(int a, int b) {
    return a + b;
}

TEST(SumaTest, Positivos) {
    EXPECT_EQ(suma(2, 3), 5);
}

TEST(SumaTest, Negativos) {
    EXPECT_EQ(suma(-2, -3), -5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
