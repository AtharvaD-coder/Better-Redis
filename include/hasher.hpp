#pragma once
#include <memory>
#include <string>
#include <vector>

using namespace std;
template <typename T> class Hasher {
	vector<pair<size_t, shared_ptr<T>>>& ring;
	size_t HashFunction(string key) const;

  public:
	Hasher(vector<pair<size_t, shared_ptr<T>>>& vec);
	shared_ptr<T> GetElement(string key);
	void AddElement();
};
