#include "../storage/database.cpp"
#include <gtest/gtest.h>

TEST(CrudOperations, InsertAndRetreive) {
	Database db;
	db.Put("key1", "value1");
	EXPECT_EQ(db.Get("key1"), "valuu1");
}

// Main function to run tests
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
