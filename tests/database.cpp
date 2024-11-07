
#include "../libs/hiredis/hiredis.h"
#include "../database/database.cpp"
#include "../database/shard.cpp"
#include "../storage/dashtable.cpp"
#include "../storage/bucket.cpp"
#include "../storage/hasher.cpp"
#include "../storage/segment.cpp"
#include <gtest/gtest.h>
#include <string>

int NO_OF_RECORDS= 1000000;

TEST(CrudOperations, InsertWithOurDatabase) {
	Database db(10);
    // auto start = std::chrono::high_resolution_clock::now();
	cout<<"Inserting "<<NO_OF_RECORDS<<" records in Database"<<endl;
	for (int i = 0; i < NO_OF_RECORDS; ++i) {
		std::string key = "key" + std::to_string(i);
		std::string value = "value" + std::to_string(i);
		db.Put(key, value);
	}
	// sleep(8);
	// cout<<db.Get("key999999")<<endl;;
	// auto end = std::chrono::high_resolution_clock::now();
	// auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	// cout<<"TIME TAKEN FOR DATABASE: "<<duration.count()<<endl;
	cout<<"Retrieving record 'key500'"<<endl;
	cout<<"Value "<<db.Get("key500")<<endl;

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


// TEST(CrudOperations, INSERTWITHDASHTABLE) {
// 	Dashtable db;
// 	auto start = std::chrono::high_resolution_clock::now();

// 	for(int i=0;i<1000000;i++){
// 		db.Put("key"+to_string(i),"value"+to_string(i));
// 	}
// 	// db.Get("key999999");

// 	auto end = std::chrono::high_resolution_clock::now();
// 	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
// 	cout<<"TIME TAKEN FOR DASHTABLE: "<<duration.count()<<endl;

// 	// cout<<db.Get("key999999")<<endl;

// }


TEST(CrudOperations, InsertWithRedis) {
	redisContext* context = redisConnect("127.0.0.1", 6379);
	if (context == nullptr || context->err) {
		if (context) {
			cout << "Error: " << context->errstr << endl;
			redisFree(context);
		} else {
			cout << "Cannot allocate redis context" << endl;
		}
		return;
	}

	cout<<"Inserting "<<NO_OF_RECORDS<<" records in Redis"<<endl;
	// auto start = std::chrono::high_resolution_clock::now();
	// cout << "Inserting 10 million records in Redis" << endl;

	for (int i = 0; i < NO_OF_RECORDS; ++i) {
		std::string key = "key" + std::to_string(i);
		std::string value = "value" + std::to_string(i);
		redisCommand(context, "SET %s %s", key.c_str(), value.c_str());
	}

	// auto end = std::chrono::high_resolution_clock::now();
	// auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	// cout << "TIME TAKEN FOR REDIS INSERTION: " << duration.count() << " microseconds" << endl;

	cout<<"Retrieving record 'key500'"<<endl;
	redisReply* reply = (redisReply*)redisCommand(context, "GET key500");
	if (reply->type == REDIS_REPLY_STRING) {
		cout << "Retrieved value: " << reply->str << endl;
	}
	freeReplyObject(reply);
	redisFree(context);
}


// Main function to run tests
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
