#include "../include/database.hpp"
#include "../include/errors.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

Database::Database() { this->hasher = make_unique<Hasher>(this->segments); }
int Database::NoOfSegments() { return this->segments.size(); }

void Database::Put(string key, string value) {
	shared_ptr<Segment> segment;
	size_t segmentIndex;
	try {
		std::cout << "PUTTING " << std::endl;
		tie(segment, segmentIndex) = hasher->GetElement(key);
	} catch (const std::exception& e) {
		std::cout << "EXCEPTION: " << e.what() << std::endl;
		hasher->AddElement();

		try {
			tie(segment, segmentIndex) = hasher->GetElement(key);
		} catch (const std::exception& e) {
			std::cout << "Failed to get segment even after adding: " << e.what()
					  << std::endl;
			return;
		}
	}

	try {
		segment->Put(key, value);
	} catch (const SegmentFullException& e) {
		std::cout << "Segment is full: " << e.what() << std::endl;
		this->Rehash(segmentIndex);
	} catch (const std::exception& e) {
		std::cout << "Unexpected exception in Put: " << e.what() << std::endl;
	}
}

void Database::Rehash(size_t segmentIndex) {
	hasher->RehashHelper(segmentIndex);
	shared_ptr<Segment> seg = segments[segmentIndex].second;
	vector<pair<string, string>> deletedValues = seg->DeleteAll();
	for (const auto& [key, value] : deletedValues) {
		seg->Put(key, value);
	};
}
string Database::Get(string key) {
	cout << "NOW TRYING GET ELEMENT " << segments.size() << endl;
	try {
		auto [segment, segmentIndex] = hasher->GetElement(key);
		cout << "FIRST STEP DONE" << endl;
		return segment->Get(key);

	} catch (const exception& e) {
		cout << "GET ERROR " << e.what() << endl;
		throw e;
	}
}

void Database::Update(string key, string value) {}
