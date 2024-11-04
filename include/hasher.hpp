
#pragma once
#include "segment.hpp"
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Hasher {
  private:
	vector<pair<size_t, Segment*>>& ring;
	size_t HashFunction(string key) const;
	void sortRing();

  public:
	Hasher(vector<pair<size_t, Segment*>>& vec);
	tuple<Segment*, size_t, size_t> GetElement(string key);
	void AddElement();
	void RehashHelper(size_t segmentIndex);
};
