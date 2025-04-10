#include "partition.h"
#include <functional>

int Partitioner::global_partition(const std::string& key) {
    return std::hash<std::string>{}(key) % 2;
}

int Partitioner::local_partition(const std::string& key) {
    return std::hash<std::string>{}(key) % 3;
}
