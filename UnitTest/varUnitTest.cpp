/**
* compile with: g++ -isystem ../KidtronicsLanguage -pthread varUnitTest.cpp ../KidtronicsLanguage/var.cpp -std=c++11  libgtest.a -o test.o
* run ./test.o
**/

#include "var.h"
#include "gtest/gtest.h"

TEST(VariableTest, ConstructorInt) {
    var object = 10;
    EXPECT_EQ(10, object);
}

TEST(VariableTest, ConstructorDouble) {
    var object = 10.5;
    EXPECT_EQ(10.5, object);
}

TEST(VariableTest, ConstructorBool) {
    var object = true;
    ASSERT_TRUE(object);
}

TEST(VariableTest, ConstructorString) {
    var object = "hello world";
    EXPECT_EQ("hello world", object);
}




int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}