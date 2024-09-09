#include <string>
#include <vector>
using namespace std;
class Bucket {
	vector<pair<string, string>> slots;
};
class Segment {
	vector<Bucket> buckets;
	void Put(string key, string value);
};

class Database {
	vector<Segment> segments;

  public:
	string Get(string key);
	void Put(string key, string value);
	void Update(string key, string value);
	void Delete(string key);
};
