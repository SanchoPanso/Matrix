#include "../matrix.h"
#include <cmath>
#include <iostream>
#include <gtest/gtest.h>


TEST(test_case_name, test_name){
    Matrix m1;
    ASSERT_EQ(m1.get_height(), 0);
    ASSERT_EQ(m1.get_width(), 0);

    Matrix m2(2, 0);
    ASSERT_EQ(m2.get_height(), 0);
    ASSERT_EQ(m2.get_width(), 0);

    Matrix m3(3, 2, 3);
    ASSERT_EQ(m3.get_height(), 3);
    ASSERT_EQ(m3.get_width(), 2);
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 2; col++)
            ASSERT_EQ(m3.get(row, col), 3);

    Matrix m4(3, 3, IDENTITY);
    ASSERT_EQ(m4.get_height(), 3);
    ASSERT_EQ(m4.get_width(), 3);
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            ASSERT_EQ(m4.get(row, col), (row == col ? 1 : 0));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
