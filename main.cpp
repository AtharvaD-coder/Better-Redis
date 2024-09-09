#include <gtest/gtest.h>

// Function to test simple arithmetic
int add(int a, int b) { return a + b; }

// Function to test string length
size_t getLength(const std::string& str) { return str.size(); }

// Function to check if a number is even
bool isEven(int number) { return number % 2 == 0; }

// Test 1: Check if add function works correctly
TEST(BareTest, AdditionTest) {
	EXPECT_EQ(add(2, 3), 5);  // Expect 2 + 3 to be 5
	EXPECT_EQ(add(-1, 1), 0); // Expect -1 + 1 to be 0
}

// Test 2: Check if string length function works correctly
TEST(BareTest, StringLengthTest) {
	EXPECT_EQ(getLength("hello"), 5); // "hello" has 5 characters
	EXPECT_EQ(getLength(""), 0);	  // Empty string has 0 length
}

// Test 3: Check if number is even
TEST(BareTest, IsEvenTest) {
	EXPECT_TRUE(isEven(4));	 // 4 is even, should return true
	EXPECT_FALSE(isEven(3)); // 3 is odd, should return false
}

// Test 4: Failing test to ensure test framework works
TEST(BareTest, FailingTest) {
	EXPECT_EQ(1 + 1,
			  3); // This is intentionally incorrect to demonstrate failure
}

// Main function to run tests
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
