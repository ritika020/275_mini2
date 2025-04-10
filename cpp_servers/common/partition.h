#pragma once
#include <string>

class Partitioner {
public:
    static int global_partition(const std::string& key); // e.g., hash % 2
    static int local_partition(const std::string& key);  // e.g., hash % 3
};
