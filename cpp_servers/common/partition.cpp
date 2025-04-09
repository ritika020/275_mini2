// #include "partition.h"
// #include <functional>

// // Apply a basic hash and modulo strategy
// int Partitioner::global_partition(const std::string& key) {
//     std::hash<std::string> hasher;
//     return hasher(key) % 2;  // 0 => Node B, 1 => Node C
// }

#include "partition.h"
#include <functional>

int Partitioner::global_partition(const std::string& key) {
    return std::hash<std::string>{}(key) % 2;
}

int Partitioner::local_partition(const std::string& key) {
    return std::hash<std::string>{}(key) % 3;
}
