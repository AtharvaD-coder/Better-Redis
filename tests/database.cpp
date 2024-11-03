
#include "../database/database.cpp"
#include "../database/shard.cpp"
#include "../storage/dashtable.cpp"
#include "../storage/bucket.cpp"
#include "../storage/hasher.cpp"
#include "../storage/segment.cpp"
#include <gtest/gtest.h>
#include <string>

TEST(CrudOperations, InsertAndRetrieve1000Records) {
	Database db(10);
    auto start = std::chrono::high_resolution_clock::now();

	// Insert 1000 records into the dashtable
	for (int i = 0; i < 1000000; ++i) {
		std::string key = "key" + std::to_string(i);
		std::string value = "value" + std::to_string(i);
		db.Put(key, value);
	}
	// sleep(8);
	cout<<db.Get("key999999")<<endl;;
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout<<"TIME TAKEN FOR DATABASE: "<<duration.count()<<endl;


	// cout<<db.Get("key999999")<<endl;
// db.print();
	// Verify that the records are correctly inserted and retrievable
	// for (int i = 0; i < 1000000; ++i) {
	// 	std::string key = "key" + std::to_string(i);
	// 	std::string expected_value = "value" + std::to_string(i);
	// 	EXPECT_EQ(db.Get(key), expected_value);
	// }

}

// TEST(CrudOperations,DeleteCheck){
// 	Dashtable db;
// 	db.Put("anurag","raut");
// 	db.Put("anurag1","raut1");
// 	db.Put("anurag2","raut2");

// 	db.Delete("anurag");

// 	cout<<db.Get("anurag1")<<endl;
// 	EXPECT_THROW(db.Get("anurag"),std::exception);
// 	EXPECT_EQ(db.Get("anurag1"),"raut1");
// 	EXPECT_EQ(db.Get("anurag2"),"raut2");


	
// }


TEST(CrudOperations, INSERTWITHDASHTABLE) {
	Dashtable db;
	auto start = std::chrono::high_resolution_clock::now();

	for(int i=0;i<1000000;i++){
		db.Put("key"+to_string(i),"value"+to_string(i));
	}
	// db.Get("key999999");

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout<<"TIME TAKEN FOR DASHTABLE: "<<duration.count()<<endl;

	// cout<<db.Get("key999999")<<endl;

}
// Main function to run tests
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
