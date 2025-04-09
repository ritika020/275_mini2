#pragma once

#include <string>

class SharedMemoryWriter {
public:
    SharedMemoryWriter(const std::string& name, size_t size);
    ~SharedMemoryWriter();
    void write(const std::string& data);

private:
    std::string shm_name_;
    size_t shm_size_;
    int shm_fd_;
    char* shm_ptr_;
};



