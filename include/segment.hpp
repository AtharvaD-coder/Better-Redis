#pragma once
#include "bucket.hpp"
#include <memory>
#include <string>
using namespace std;
class Segment {
	vector<shared_ptr<Bucket>> buckets;
	pair<shared_ptr<Bucket>, size_t> GetBucket(string key,size_t segmentHash) const;

  public:
	Segment();
	void Put(string key, string value,size_t segmentHash);
	string Get(string key,size_t segmentHash);
	void Delete(string key,size_t segmentHash);
	vector<pair<string, string>> DeleteAll();
	void print();
};
