/**
* compile with: g++ -isystem ../KidtronicsLanguage -pthread varUnitTest.cpp ../KidtronicsLanguage/var.cpp -std=c++11  libgtest.a -o test.o
* run ./test.o
**/

#include "var.h"
#include "gtest/gtest.h"

using namespace std;

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
    var object2 = false;
    ASSERT_FALSE(object2);
}

TEST(VariableTest, ConstructorString) {
    var object = "hello world";
    EXPECT_EQ("hello world", object);
}

TEST(VariableTest, AssignmentOperatorInt) {
    var object = 10;
    EXPECT_EQ(10, object);
    object = 20;
    EXPECT_EQ(20, object);
    var object2 = 30;
    object = object2;
    EXPECT_EQ(30, object);
}

TEST(VariableTest, AssignmentOperatorDouble) {
    var object = 10.5;
    EXPECT_EQ(10.5, object);
    object = 20.5;
    EXPECT_EQ(20.5, object);
    var object2 = 30.5;
    object = object2;
    EXPECT_EQ(30.5, object);
}

TEST(VariableTest, AssignmentOperatorIntToDouble) {
    var object = 10;
    EXPECT_EQ(10, object);
    object = 20.5;
    EXPECT_EQ(20.5, object);
    var object2 = 30;
    object2 = object;
    EXPECT_EQ(20.5, object2);
}

TEST(VariableTest, AssignmentOperatorDoubleToInt) {
    var object = 10.5;
    EXPECT_EQ(10.5, object);
    object = 20;
    EXPECT_EQ(20, object);
    var object2 = 30.5;
    object2 = object;
    EXPECT_EQ(20, object2);
}

TEST(VariableTest, AssignmentOperatorBoolean) {
    var object = false;
    ASSERT_FALSE(object);
    object = true;
    ASSERT_TRUE(object);
    var object2 = false;
    object = object2;
    ASSERT_FALSE(object);
}

TEST(VariableTest, AssignmentOperatorString) {
    var object = "Hello";
    EXPECT_EQ("Hello", object);
    object = "world";
    EXPECT_EQ("world", object);
    var object2 = "foxtrot";
    object = object2;
    EXPECT_EQ("foxtrot", object);
}

TEST(VariableTest, EqualOperatorInt) {
    var object = 10;
    var object2 = 10;
    var object3 = 11;
    ASSERT_TRUE(object == 10);
    ASSERT_TRUE(object == object2);
    ASSERT_FALSE(object == 11);
    ASSERT_FALSE(object == object3);
}

TEST(VariableTest, EqualOperatordouble) {
    var object = 10.5;
    var object2 = 10.5;
    var object3 = 11.5;
    ASSERT_TRUE(object == 10.5);
    ASSERT_TRUE(object == object2);
    ASSERT_FALSE(object == 11.5);
    ASSERT_FALSE(object == object3);
}

TEST(VariableTest, EqualOperatorIntAndDouble) {
    var object = 10;
    var object2 = 10.0;
    var object3 = 10.5;
    ASSERT_TRUE(object == 10.0);
    ASSERT_TRUE(object == object2);
    ASSERT_FALSE(object == 11.5);
    ASSERT_FALSE(object == object3);
}

TEST(VariableTest, EqualOperatorBoolean) {
    var object = true;
    ASSERT_TRUE(object == true);
    ASSERT_TRUE(object == 1);
    ASSERT_TRUE(object == 1.0);
    ASSERT_FALSE(object == 11);
    ASSERT_FALSE(object == 1.5);
    ASSERT_FALSE(object == 0.5);
    object = false;
    ASSERT_TRUE(object == false);
    ASSERT_TRUE(object == 0);
    ASSERT_TRUE(object == 0.0);
    ASSERT_FALSE(object == 11);
    ASSERT_FALSE(object == 0.5);
    ASSERT_FALSE(object == 0.5);
}

TEST(VariableTest, EqualOperatorString) {
    var str = "hello";
    var str2 = "world";
    var str3 = "hello";
    ASSERT_TRUE(str == "hello");
    ASSERT_TRUE(str == str3);
    ASSERT_FALSE(str == "world");
    ASSERT_FALSE(str == str2);
    ASSERT_FALSE(str == 1);   
}

TEST(VariableTest, NotEqualOperatordouble) {
    var object = 10.5;
    var object2 = 10.5;
    var object3 = 11.5;
    ASSERT_FALSE(object != 10.5);
    ASSERT_FALSE(object != object2);
    ASSERT_TRUE(object != 11.5);
    ASSERT_TRUE(object != object3);
}

TEST(VariableTest, NotEqualOperatorInt) {
    var object = 10;
    var object2 = 10;
    var object3 = 11;
    ASSERT_FALSE(object != 10);
    ASSERT_FALSE(object != object2);
    ASSERT_TRUE(object != 11);
    ASSERT_TRUE(object != object3);
}

TEST(VariableTest, NotEqualOperatorIntAndDouble) {
    var object = 10;
    var object2 = 10.0;
    var object3 = 10.5;
    ASSERT_FALSE(object != 10.0);
    ASSERT_FALSE(object != object2);
    ASSERT_TRUE(object != 11.5);
    ASSERT_TRUE(object != object3);
}

TEST(VariableTest, NotEqualOperatorBoolean) {
    var object = true;
    ASSERT_FALSE(object != true);
    ASSERT_FALSE(object != 1);
    ASSERT_FALSE(object != 1.0);
    ASSERT_TRUE(object != 11);
    ASSERT_TRUE(object != 1.5);
    ASSERT_TRUE(object != 0.5);
    object = false;
    ASSERT_FALSE(object != false);
    ASSERT_FALSE(object != 0);
    ASSERT_FALSE(object != 0.0);
    ASSERT_TRUE(object != 11);
    ASSERT_TRUE(object != 0.5);
    ASSERT_TRUE(object != 0.5);
}

TEST(VariableTest, LessThanOperatorInt) {
    var object = 10;
    var object2 = 11;
    var object3 = 9;
    var object4 = 10;
    ASSERT_TRUE(object < 11);
    ASSERT_TRUE(object < object2);
    ASSERT_FALSE(object < 9);
    ASSERT_FALSE(object < object3);
    ASSERT_FALSE(object < object4);
}

TEST(VariableTest, LessThanOperatorDouble) {
    var object = 10.5;
    var object2 = 11.0;
    var object3 = 10.4;
    var object4 = 10.5;
    ASSERT_TRUE(object < 11);
    ASSERT_TRUE(object < object2);
    ASSERT_FALSE(object < 9);
    ASSERT_FALSE(object < object3);
    ASSERT_FALSE(object < object4);
}

TEST(VariableTest, LessThanOperatorIntAndDouble) {
    var object = 10;
    var object2 = 11.0;
    var object3 = 10.0;
    var object4 = 9.9;
    ASSERT_TRUE(object < 10.5);
    ASSERT_TRUE(object < object2);
    ASSERT_FALSE(object < 9);
    ASSERT_FALSE(object < object3);
    ASSERT_FALSE(object < object4);
}

TEST(VariableTest, LessThanEqualOperatorInt) {
    var object = 10;
    var object2 = 11;
    var object3 = 9;
    var object4 = 10;
    ASSERT_TRUE(object <= 11);
    ASSERT_TRUE(object <= object2);
    ASSERT_FALSE(object <= 9);
    ASSERT_FALSE(object <= object3);
    ASSERT_TRUE(object <= object4);
}

TEST(VariableTest, LessThanEqualOperatorDouble) {
    var object = 10.5;
    var object2 = 11.0;
    var object3 = 10.4;
    var object4 = 10.5;
    ASSERT_TRUE(object <= 11);
    ASSERT_TRUE(object <= object2);
    ASSERT_FALSE(object <= 9);
    ASSERT_FALSE(object <= object3);
    ASSERT_TRUE(object <= object4);
}

TEST(VariableTest, LessThanEqualOperatorIntAndDouble) {
    var object = 10;
    var object2 = 11.0;
    var object3 = 10.0;
    var object4 = 9.9;
    ASSERT_TRUE(object <= 10.5);
    ASSERT_TRUE(object <= object2);
    ASSERT_FALSE(object <= 9);
    ASSERT_TRUE(object <= object3);
    ASSERT_FALSE(object <= object4);
}

TEST(VariableTest, GreaterThanOperatorInt) {
    var object = 10;
    var object2 = 11;
    var object3 = 9;
    var object4 = 10;
    ASSERT_FALSE(object > 11);
    ASSERT_FALSE(object > object2);
    ASSERT_TRUE(object > 9);
    ASSERT_TRUE(object > object3);
    ASSERT_FALSE(object > object4);
}

TEST(VariableTest, GreaterThanOperatorDouble) {
    var object = 10.5;
    var object2 = 11.0;
    var object3 = 10.4;
    var object4 = 10.5;
    ASSERT_FALSE(object > 11);
    ASSERT_FALSE(object > object2);
    ASSERT_TRUE(object > 9);
    ASSERT_TRUE(object > object3);
    ASSERT_FALSE(object > object4);
}

TEST(VariableTest, GreaterThanOperatorIntAndDouble) {
    var object = 10;
    var object2 = 11.0;
    var object3 = 10.0;
    var object4 = 9.9;
    ASSERT_FALSE(object > 10.5);
    ASSERT_FALSE(object > object2);
    ASSERT_TRUE(object > 9);
    ASSERT_FALSE(object > object3);
    ASSERT_TRUE(object > object4);
}

TEST(VariableTest, GreaterEqualOperatorInt) {
    var object = 10;
    var object2 = 11;
    var object3 = 9;
    var object4 = 10;
    ASSERT_FALSE(object >= 11);
    ASSERT_FALSE(object >= object2);
    ASSERT_TRUE(object >= 9);
    ASSERT_TRUE(object >= object3);
    ASSERT_TRUE(object >= object4);
}

TEST(VariableTest, GreaterEqualOperatorDouble) {
    var object = 10.5;
    var object2 = 11.0;
    var object3 = 10.4;
    var object4 = 10.5;
    ASSERT_FALSE(object >= 11);
    ASSERT_FALSE(object >= object2);
    ASSERT_TRUE(object >= 9);
    ASSERT_TRUE(object >= object3);
    ASSERT_TRUE(object >=object4);
}

TEST(VariableTest, GreaterEqualOperatorIntAndDouble) {
    var object = 10;
    var object2 = 11.0;
    var object3 = 10.0;
    var object4 = 9.9;
    ASSERT_FALSE(object >= 10.5);
    ASSERT_FALSE(object >= object2);
    ASSERT_TRUE(object >= 9);
    ASSERT_TRUE(object >= object3);
    ASSERT_TRUE(object >= object4);
}

TEST(VariableTest, CompareVariableString) {
    var str = "hello";
    var str2 = "hello";
    var str3 = "world";
    ASSERT_FALSE(str < str2);
    ASSERT_FALSE(str < "hello");
    ASSERT_TRUE(str < str3);
    ASSERT_TRUE(str <= str2);
    ASSERT_TRUE(str <= "hello");
    ASSERT_TRUE(str <= str3);
    ASSERT_FALSE(str > str2);
    ASSERT_FALSE(str > "hello");
    ASSERT_FALSE(str > str3);
    ASSERT_TRUE(str >= str2);
    ASSERT_TRUE(str >= "hello");
    ASSERT_FALSE(str >= str3);
}

TEST(VariableTest, AdditionInteger) {
    var object = 10;
    var object2 = 5;
    var object3 = 5.5;
    EXPECT_EQ(object + 5, 15);
    EXPECT_EQ(object + object2, 15);
    EXPECT_EQ(object + 5.5, 15.5);
    EXPECT_EQ(object + object3, 15.5);
}

TEST(VariableTest, SubtractionInteger) {
    var object = 10;
    var object2 = 5;
    var object3 = 5.5;
    EXPECT_EQ(object - 5, 5);
    EXPECT_EQ(object - object2, 5);
    EXPECT_EQ(object - 5.5, 4.5);
    EXPECT_EQ(object - object3, 4.5);
}

TEST(VariableTest, AdditionDouble) {
    var object = 10.0f;
    var object2 = 5;
    var object3 = 5.5;
    EXPECT_EQ(object + 5, 15);
    EXPECT_EQ(object + object2, 15);
    EXPECT_EQ(object + 5.5, 15.5);
    EXPECT_EQ(object + object3, 15.5);
}

TEST(VariableTest, SubtractionDouble) {
    var object = 10.0f;
    var object2 = 5;
    var object3 = 5.5;
    EXPECT_EQ(object - 5, 5);
    EXPECT_EQ(object - object2, 5);
    EXPECT_EQ(object - 5.5, 4.5);
    EXPECT_EQ(object - object3, 4.5);
}

TEST(VariableTest, AdditionString) {
    var str = "hello";
    var str2 = "world";
    EXPECT_EQ("helloworld", str+"world");
    EXPECT_EQ("helloworld", str+str2);
}

TEST(VariableTest, IncrementInteger) {
    int count = 0;
    for(var i = 0; i < 10; i++) {
        EXPECT_EQ(count, i);
        count++;
    }
    count = 0;
    for(var i = 0; i < 10; ++i) {
        EXPECT_EQ(count, i);
        count++;
    }
}

TEST(VariableTest, IncrementDouble) {
    double count = 0.5;
    for(var i = 0.5; i < 10; i++) {
        EXPECT_EQ(count, i);
        count++;
    }
    count = 0.5;
    for(var i = 0.5; i < 10; ++i) {
        EXPECT_EQ(count, i);
        count++;
    }
}

TEST(VariableTest, DecrementInteger) {
    int count = 10;
    for(var i = 10; i > 0; i--) {
        EXPECT_EQ(count, i);
        count--;
    }
    count = 10;
    for(var i = 10; i > 0; --i) {
        EXPECT_EQ(count, i);
        count--;
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}