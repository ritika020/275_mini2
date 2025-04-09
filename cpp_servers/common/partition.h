// #pragma once
// #include <string>

// // Hash-based partitioning logic
// // Used to decide whether to send to Node B or Node C
// class Partitioner {
// public:
//     // Returns 0 or 1 based on hash(key) % 2
//     static int global_partition(const std::string& key);
// };



#pragma once
#include <string>

class Partitioner {
public:
    static int global_partition(const std::string& key); // e.g., hash % 2
    static int local_partition(const std::string& key);  // e.g., hash % 3
};
