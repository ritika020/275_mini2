#include "shm_writer.h"
#include <fcntl.h>    // For O_* constants
#include <sys/mman.h> // For shm_open, mmap
#include <unistd.h>   // For ftruncate, close
#include <cstring>    // For memcpy
#include <iostream>

SharedMemoryWriter::SharedMemoryWriter(const std::string& name, size_t size)
    : shm_name_(name), shm_size_(size), shm_fd_(-1), shm_ptr_(nullptr) {

    shm_fd_ = shm_open(shm_name_.c_str(), O_CREAT | O_RDWR, 0666);
    if (shm_fd_ == -1) {
        perror("shm_open");
        return;
    }

    if (ftruncate(shm_fd_, shm_size_) == -1) {
        perror("ftruncate");
        return;
    }

    shm_ptr_ = static_cast<char*>(mmap(0, shm_size_, PROT_WRITE, MAP_SHARED, shm_fd_, 0));
    if (shm_ptr_ == MAP_FAILED) {
        perror("mmap");
        return;
    }
}

SharedMemoryWriter::~SharedMemoryWriter() {
    if (shm_ptr_ != nullptr) {
        munmap(shm_ptr_, shm_size_);
    }
    if (shm_fd_ != -1) {
        close(shm_fd_);
    }
    shm_unlink(shm_name_.c_str());
}

void SharedMemoryWriter::write(const std::string& data) {
    if (shm_ptr_ != nullptr && data.size() < shm_size_) {
        memcpy(shm_ptr_, data.c_str(), data.size());
    }
}
