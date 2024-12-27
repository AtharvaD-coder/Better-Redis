#include "../database/database.cpp"
#include "../database/shard.cpp"
#include "../storage/bucket.cpp"
#include "../storage/dashtable.cpp"
#include "../storage/hasher.cpp"
#include "../storage/segment.cpp"
#include "dashtable.hpp"
#include <iostream>
#include "../include/quic_server.hpp"

using namespace std;

int main(int argc, char** argv) {
	Database* db = new Database();
	db->Put("anurag", "raut");

	QuicServer server;
    server.RunServer();

	delete db;
}
