#pragma once
#include "hasher.hpp"
#include "segment.hpp"
#include "transaction.hpp"
#include <memory>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Dashtable {
	vector<pair<size_t, shared_ptr<Segment>>> segments;
	queue<Transaction> transaction_queue;
	unique_ptr<Hasher> hasher;

  public:
	Dashtable();
	int rehashCounter=0;
	int NoOfSegments();
	string Get(string key);
	void Put(string key, string value);
	void Update(string key, string value);
	void Delete(string key);
	void Rehash(size_t segmentIndex);
	void print();
};
