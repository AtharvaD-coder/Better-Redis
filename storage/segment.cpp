#include "../include/segment.hpp"
#include "../include/bucket.hpp"
#include "../include/errors.hpp"
#include "../include/globals.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
using namespace std;
void Segment::Put(string key, string value,size_t segmentHash) {

	pair<shared_ptr<Bucket>, size_t> getBuckResult = GetBucket(key,segmentHash);
	shared_ptr<Bucket> buck = getBuckResult.first;
	size_t bucketIndex = getBuckResult.second;
	try {
		buck->Put(key, value);
		// cout << "Bucket index: " << bucketIndex << endl;
	} catch (const BucketFullException& e) {
		shared_ptr<Bucket> newbucket =
			buckets[(bucketIndex + 1) % buckets.size()];
		try {
			newbucket->Put(key, value);
			// cout << "Bucket index: " << (bucketIndex + 1) % buckets.size()
			// 	 << endl;
		} catch (const BucketFullException& e) { throw SegmentFullException(); }
	}
}

string Segment::Get(string key,size_t segmentHash) {
    
    pair<shared_ptr<Bucket>, size_t> getBuckResult = GetBucket(key,segmentHash);
	shared_ptr<Bucket> buck = getBuckResult.first;
	size_t bucketIndex = getBuckResult.second;
	// cout << "GETTING BUCKET INDEX: " << bucketIndex << endl;
	try {
		return buck->Get(key);

	} catch (const std::exception& e) {
		try {

			shared_ptr<Bucket> newbuck =
				buckets[(bucketIndex + 1) % buckets.size()];

			return newbuck->Get(key);
		} catch (const std::exception& e) { throw e; }
	}

	
}

pair<shared_ptr<Bucket>, size_t> Segment::GetBucket(string key,size_t segmentHash) const {
	string combinedKey = key + to_string(segmentHash);
	size_t hashValue = hash<string>{}(combinedKey);

	std::size_t bucketIndex = hashValue % BUCKET_SIZE;
	// cout << "HASH VALUE FOR KEY " << key << " IS: " << bucketIndex << endl;
	return make_pair(buckets[bucketIndex], bucketIndex);
}

Segment::Segment() {
	for (size_t i = 0; i < BUCKET_SIZE; i++) {
		buckets.push_back(make_shared<Bucket>());
	}
	for (auto& bucket : buckets) {
		bucket = make_shared<Bucket>();
	}
}

vector<pair<string, string>> Segment::DeleteAll() {
	vector<pair<string, string>> values;
	for (auto buck : buckets) {
		auto deletedValues = buck->DeleteAll();
		values.insert(values.end(), deletedValues.begin(), deletedValues.end());
	}

	return values;
}

void Segment::print() {
	int index = 0;
	for (auto& bucks : buckets) {
		cout << "Bucket: " << index++ << endl;
		bucks->print();
	}

	cout << endl;
}