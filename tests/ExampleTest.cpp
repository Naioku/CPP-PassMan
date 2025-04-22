#include "gtest/gtest.h"
#include "ExampleClass.h"

TEST(ExampleClassTestSuite, Add)
{
    ExampleClass exampleClass;
    EXPECT_EQ(exampleClass.add(1, 2), 3);
    // EXPECT_EQ(3, 3);
}
