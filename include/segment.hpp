#pragma once
#include "bucket.hpp"
#include <memory>
#include <string>
using namespace std;
class Segment {
	vector<shared_ptr<Bucket>> buckets;
	shared_ptr<Bucket> GetBucket(string key) const;

  public:
	Segment();
	void Put(string key, string value);
	string Get(string key);
};
