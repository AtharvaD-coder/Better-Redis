#include "../include/segment.hpp"
#include "../include/bucket.hpp"
#include "../include/errors.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
using namespace std;
void Segment::Put(string key, string value) {

	pair<shared_ptr<Bucket>, size_t> getBuckResult = GetBucket(key);
	shared_ptr<Bucket> buck = getBuckResult.first;
	size_t bucketIndex = getBuckResult.second;

	try {
		buck->Put(key, value);
	} catch (const BucketFullException& e) {
		cout << "TRYING TO INSERT IN NEW BUCKET" << e.what() << endl;
		shared_ptr<Bucket> newbucket =
			buckets[(bucketIndex + 1) % buckets.size()];
		try {
			newbucket->Put(key, value);
		} catch (const BucketFullException& e) { throw SegmentFullException(); }
	}
}

string Segment::Get(string key) {
	pair<shared_ptr<Bucket>, size_t> getBuckResult = GetBucket(key);
	shared_ptr<Bucket> buck = getBuckResult.first;
	size_t bucketIndex = getBuckResult.second;

	return buck->Get(key);
}

pair<shared_ptr<Bucket>, size_t> Segment::GetBucket(string key) const {
	size_t hashValue = hash<string>{}(key);

	std::size_t bucketIndex = hashValue % buckets.size();
	cout << "BUCKET INDEX: " << bucketIndex << endl;
	return make_pair(buckets[bucketIndex], bucketIndex);
}

Segment::Segment() {
	cout << "LES GOO" << endl;
	buckets.resize(10, make_shared<Bucket>());
}

vector<pair<string, string>> Segment::DeleteAll() {
	vector<pair<string, string>> values;
	for (auto buck : buckets) {
		auto deletedValues = buck->DeleteAll();
		values.insert(values.end(), deletedValues.begin(), deletedValues.end());
	}

	return values;
}
