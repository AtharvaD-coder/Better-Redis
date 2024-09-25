
#include "../include/bucket.hpp"
#include "../include/errors.hpp"
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

Bucket::Bucket() { slots.resize(10); }

void Bucket::Put(string key, string value) {
	for (auto& slot : slots) {
		if (slot.first.empty()) {
			slot.first = key;
			slot.second = value;
			return;
		}
	}
	throw BucketFullException();
}

string Bucket::Get(string key) {
	for (auto& slot : slots) {
		if (slot.first == key) {
			return slot.second;
		}
	}
	throw runtime_error("VALUE NOT PRESENT");
}

vector<pair<string, string>> Bucket::DeleteAll() {
	vector<pair<string, string>> values;
	for (auto& slot : slots) {
		if (!slot.first.empty()) {
			values.emplace_back(slot.first, slot.second);
			slot.first.clear();
			slot.second.clear();
		}
	}
	return values;
}
