#include "../include/segment.hpp"
#include "../include/bucket.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
using namespace std;
void Segment::Put(string key, string value) {
	try {

		shared_ptr<Bucket> buck = GetBucket(key);
		buck->Put(key, value);
	} catch (const exception& e) {
		cout << "Exeption " << e.what() << endl;
		// insert new one
	}
}

string Segment::Get(string key) {
	shared_ptr<Bucket> buck = GetBucket(key);
	return buck->Get(key);
}

shared_ptr<Bucket> Segment::GetBucket(string key) const {
	size_t hashValue = hash<string>{}(key);

	std::size_t bucketIndex = hashValue % buckets.size();
	cout << "BUCKET INDEX: " << bucketIndex << endl;
	return (buckets[bucketIndex]);
}

Segment::Segment() {
	cout << "LES GOO" << endl;
	buckets.resize(10, make_shared<Bucket>());
}
