#include "../storage/bucket.cpp"
#include "../storage/database.cpp"
#include "../storage/hasher.cpp"
#include "../storage/segment.cpp"
#include "database.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	Database* db = new Database();
	db->Put("anurag", "raut");
}
