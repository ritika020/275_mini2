#include "shared_memory.hpp"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

void write_to_shared_memory(const std::string& key, const std::string& data) {
    int shm_fd = shm_open(key.c_str(), O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 1024);
    void* ptr = mmap(0, 1024, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    memcpy(ptr, data.c_str(), data.size());
    munmap(ptr, 1024);
    close(shm_fd);
    std::cout << "[SHM] Stored in " << key << ": " << data << std::endl;
}
