#include <iostream>
#include <vector>
#include <string>

unsigned int hashFunction(const std::string& key) {
    unsigned int hash = 0;
    for (char c : key) {
        hash = hash * 101  +  c; 
    }
    return hash;
}

unsigned int getBucketIndex(const std::string& key, unsigned int numBuckets) {
    unsigned int hashValue = hashFunction(key);
    return hashValue % numBuckets;
}

int main() {
    unsigned int numBuckets = 10;

    // Example keys to hash
    std::vector<std::string> keys = {"apple", "banana", "cherry", "date", "elderberry"};

    // Hash the keys and place them in buckets
    for (const std::string& key : keys) {
        unsigned int bucketIndex = getBucketIndex(key, numBuckets);
        std::cout << "Key: " << key << " -> Bucket: " << bucketIndex << std::endl;
    }

    return 0;
}
