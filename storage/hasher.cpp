#include "../include/hasher.hpp"
#include "../include/segment.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

Hasher::Hasher(vector<pair<size_t, shared_ptr<Segment>>>& ring) : ring(ring) {}

pair<shared_ptr<Segment>, size_t> Hasher::GetElement(string key) {
	if (ring.empty()) {
		throw std::runtime_error("No Segments available");
	}

	size_t hashValue = HashFunction(key);
	auto it = lower_bound(ring.begin(), ring.end(),
						  make_pair(hashValue, shared_ptr<Segment>{}),
						  [](const pair<size_t, shared_ptr<Segment>>& a,
							 const pair<size_t, shared_ptr<Segment>>& b) {
							  return a.first < b.first;
						  });

	if (it == ring.end()) {
		cout << "HASHER FOUND ELEMENT: " << ring.front().first << endl;
		return {ring.front().second,
				0}; // Returning index 0 for the front element
	}

	size_t index = distance(ring.begin(), it);
	cout << "HASHER FOUND ELEMENT: " << it->first << endl;
	return {it->second, index};
}

void Hasher::AddElement() {
	size_t hashValue = HashFunction(to_string(ring.size()));
	ring.push_back(make_pair(hashValue, make_shared<Segment>()));
	sort(ring.begin(), ring.end(),
		 [](const pair<size_t, shared_ptr<Segment>>& a,
			const pair<size_t, shared_ptr<Segment>>& b) {
			 return a.first < b.first;
		 });
}

size_t Hasher::HashFunction(string key) const {
	hash<string> hash_fn;
	cout << "KEY: " << key << endl;
	size_t hashValue = hash_fn(key);
	cout << "Hash Value: " << hashValue << endl;
	return hashValue;
}

void Hasher::RehashHelper(size_t segmentIndex) {
	size_t currentElementHashValue = ring[segmentIndex].first;
	size_t prevElementHashValue;
	if (segmentIndex != 0) {
		prevElementHashValue = ring[segmentIndex - 1].first;
	} else {
		prevElementHashValue = ring.back().first;
	}

	size_t midhashValue = (currentElementHashValue - prevElementHashValue) / 2;

	// Insert a new segment in the ring at the specified index
	ring.insert(ring.begin() + segmentIndex,
				make_pair(midhashValue, make_shared<Segment>()));
}
