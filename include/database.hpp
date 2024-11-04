#pragma once
#include <vector>
#include <memory>
#include <string>
#include "./shard.hpp"

using namespace std;

class Database {

	int noOfShards;
	vector<Shard*> shards;
    int getShard(string key);

  public:
    Database(int noOfShards);
    ~Database();
	string Get(string key);
	void Put(string key, string value);
	void Delete(string key);
};