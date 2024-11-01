
#include "../storage/database.cpp"
#include "../storage/bucket.cpp"
#include "../storage/hasher.cpp"
#include "../storage/segment.cpp"
#include <gtest/gtest.h>
#include <string>

TEST(CrudOperations, InsertAndRetrieve1000Records) {
	Database db;

	// Insert 1000 records into the database
	for (int i = 0; i < 10000000; ++i) {
		std::string key = "key" + std::to_string(i);
		std::string value = "value" + std::to_string(i);
		db.Put(key, value);
	}
	cout<<"NO OF REHASHES "<<db.rehashCounter<<endl;
	// cout<<db.Get("key999999")<<endl;
// db.print();
	// Verify that the records are correctly inserted and retrievable
	// for (int i = 0; i < 1000000; ++i) {
	// 	std::string key = "key" + std::to_string(i);
	// 	std::string expected_value = "value" + std::to_string(i);
	// 	EXPECT_EQ(db.Get(key), expected_value);
	// }

}

// Main function to run tests
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
