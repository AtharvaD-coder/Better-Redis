#include "../include/database.hpp"

Database::Database(int noOfShards){
    this->noOfShards=noOfShards;
    for(int i=0;i<noOfShards;i++){
        shards.push_back(new Dashtable());
    }
}
