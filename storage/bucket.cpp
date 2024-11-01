
#include "../include/bucket.hpp"
#include "../include/errors.hpp"
#include "../include/globals.hpp"
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

Bucket::Bucket() { slots.resize(SLOT_SIZE); }

void Bucket::Put(string key, string value) {
	for (size_t i = 0; i < slots.size(); ++i) {
		auto& slot = slots[i];
		if (slot.first.empty()) {
			// cout<<"PUTTING IN SLOT: "<<i<<endl;
			slot.first = key;
			slot.second = value;
			return;
		}
	}
	throw BucketFullException();
}

string Bucket::Get(string key) {
	for (auto& slot : slots) {
		// cout << "SLOT FIRST " << slot.first << endl;
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
void Bucket::Delete(string key) {
	for (auto& slot : slots) {
		if (slot.first == key) {
			slot.first.clear();
			slot.second.clear();
			return;
		}
	}
	throw runtime_error("VALUE NOT PRESENT");
}

void Bucket::print(){
	for (auto& slot : slots) {
		if(slot.first.empty()){
		// cout<<"_ ";

		}
		else{

		// cout<<slot.first<<" ";
		}
	}
	// cout<<endl;
}