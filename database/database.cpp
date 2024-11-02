#include <thread>
#include <future>
#include <iostream>
#include "../include/database.hpp"
#include "../include/shard.hpp"


using namespace std;

Database::Database(int noOfShards=thread::hardware_concurrency()){
    this->noOfShards=noOfShards;
    cout<<"NO OF SHARDS: "<<noOfShards<<endl;
    for(int i=0;i<noOfShards;i++){
        shards.emplace_back(make_shared<Shard>());
    }
    // cout<<"DONE"<<endl;
}

int Database::getShard(string key){
    hash<string> hash_fn;
    size_t hashValue = hash_fn(key);
    return hashValue%noOfShards;
}

string Database::Get(string key){
    int shardIndex=getShard(key);
    shared_ptr<Shard> shard=shards[shardIndex];
    future<string> resultFuture = shard->submitTransaction(Transaction{GET,key,""});
    string result = resultFuture.get();
    return result;
}

void Database::Put(string key, string value){
    int shardIndex=getShard(key);
    shared_ptr<Shard> shard=shards[shardIndex];
    future<string> resultFuture = shard->submitTransaction(Transaction{PUT,key,value});
    string result = resultFuture.get();

}

void Database::Delete(string key){
    int shardIndex=getShard(key);
    shared_ptr<Shard> shard=shards[shardIndex];
    future<string> resultFuture = shard->submitTransaction(Transaction{DELETE,key,""});
    string result = resultFuture.get();
}

Database::~Database() {
    cout<<"DatabseDESTRUCTOR CALLED"<<endl;
    shards.clear(); 
}
