#pragma once
#include <string>
#include <vector>
using namespace std;

class Bucket {
	vector<pair<string, string>> slots;

  public:
	Bucket();
	void Put(string key, string value);
	string Get(string key);
	vector<pair<string, string>> DeleteAll();
	void print();
};
