#include "../include/hasher.hpp"
#include "../include/globals.hpp"
#include "../include/segment.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>

Hasher::Hasher(vector<pair<size_t, shared_ptr<Segment>>>& ring) : ring(ring) {
	for (size_t i = 0; i < SEGMENT_SIZE; i++) {
		AddElement();
	}
}

tuple<shared_ptr<Segment>, size_t, size_t> Hasher::GetElement(string key) {
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

	// If the key is greater than the last element in the ring, return the first
	// element

	// cout << "FOR KEY: " << key << " GOT HASH VALUE: " << hashValue << endl;
	if (it == ring.end()) {
		return {ring.front().second, 0,
				ring.front().first}; // Returning index 0 for the front element
	}

	size_t index = distance(ring.begin(), it);
	// cout << "RETURNING INDEX: " << index << endl;
	return {it->second, index, it->first};
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
	size_t hashValue = hash_fn(key);

	return (hashValue % MAX_RING_SIZE);
}

int getRingValue(int val) { return (MAX_RING_SIZE + val) % MAX_RING_SIZE; }

void Hasher::RehashHelper(size_t segmentIndex) {
	long long currentElementHashValue = ring[segmentIndex].first;
	long long prevElementHashValue = 0;
	long long midhashValue = 0;
	if (this->ring.size() == 1) {
		midhashValue =
			getRingValue(currentElementHashValue - (MAX_RING_SIZE / 2));
	} else if (segmentIndex == 0) {
		prevElementHashValue = ring.back().first;

		midhashValue = getRingValue(currentElementHashValue -
									((currentElementHashValue +
									  (MAX_RING_SIZE - prevElementHashValue)) /
									 2));
	} else {
		prevElementHashValue = ring[segmentIndex - 1].first;
		midhashValue = getRingValue(
			prevElementHashValue +
			((currentElementHashValue - prevElementHashValue) / 2));
	}

	ring.insert(ring.begin() + segmentIndex,
				make_pair(midhashValue, std::make_shared<Segment>()));

	// print all the elements in the ring


	std::sort(ring.begin(), ring.end(),
			  [](const std::pair<size_t, std::shared_ptr<Segment>>& a,
				 const std::pair<size_t, std::shared_ptr<Segment>>& b) {
				  return a.first < b.first;
			  });
}
