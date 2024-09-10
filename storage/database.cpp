#include "../include/database.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

Database::Database() {
	this->hasher = make_unique<Hasher<Segment>>(this->segments);
}
int Database::NoOfSegments() { return this->segments.size(); }

void Database::Put(string key, string value) {
	try {
		cout << "PUTTING " << endl;
		shared_ptr<Segment> segment = hasher->GetElement(key);
		segment->Put(key, value);

	} catch (const exception& e) {
		// no segment in seg array
		cout << "EXEPTION:" << endl;
		hasher->AddElement();
		Put(key, value);
	}
}

string Database::Get(string key) {
	cout << "NOW TRYING GET ELEMENT " << segments.size() << endl;
	try {
		shared_ptr<Segment> segment = hasher->GetElement(key);
		cout << "FIRST STEP DONE" << endl;
		return segment->Get(key);

	} catch (const exception& e) {
		cout << "GET ERROR " << e.what() << endl;
		throw e;
	}
}

void Database::Update(string key, string value) {}
