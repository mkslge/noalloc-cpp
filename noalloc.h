//
// Created by Mark on 1/25/26.
//

#ifndef NOALLOC_H
#define NOALLOC_H

#include <cstddef>

namespace NoAllocDetail {
    extern thread_local std::size_t alloc_count;
}


void* operator new(std::size_t size);
void* operator new[](std::size_t size);
void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;

enum class noalloc_mode {
    terminate, log
};


class noalloc {
private:
    size_t alloc_at_start_ {};
    noalloc_mode mode_;
public:
    explicit noalloc(noalloc_mode mode = noalloc_mode::terminate);

    ~noalloc() noexcept;
};


//
// Created by Mark on 1/25/26.
//

#include "noalloc.h"
#include <cstdlib>
#include <new>
#include <iostream>

namespace NoAllocDetail {
    thread_local std::size_t alloc_count = 0;
    thread_local int noalloc_depth = 0;
}

void* operator new(std::size_t size) {

    if (NoAllocDetail::noalloc_depth != 0) {
        NoAllocDetail::alloc_count++;
    }

    void*ptr = std::malloc(size);
    if (!ptr) {
        throw std::bad_alloc();
    }
    return ptr;
}

void* operator new[](std::size_t size) {
    if (NoAllocDetail::noalloc_depth != 0) {
        NoAllocDetail::alloc_count++;
    }
    void*ptr = std::malloc(size);
    if (!ptr) {
        throw std::bad_alloc();
    }
    return ptr;
}


void operator delete(void* ptr) noexcept {
    std::free(ptr);
}

void operator delete[](void* ptr) noexcept {
    std::free(ptr);
}


noalloc::noalloc(noalloc_mode mode) : alloc_at_start_(NoAllocDetail::alloc_count), mode_(mode) {
    NoAllocDetail::noalloc_depth++;
}

noalloc::~noalloc() noexcept {
    NoAllocDetail::noalloc_depth--;
    size_t alloc_at_end = NoAllocDetail::alloc_count;
    if (alloc_at_end > alloc_at_start_) {
        if (mode_ == noalloc_mode::terminate) {
            std::terminate();
        } else if (mode_ == noalloc_mode::log){
            size_t diff = alloc_at_end - alloc_at_start_;
            std::cerr << "[noalloc] "
            << diff
            << " allocation(s) occurred in scope.\n";

        }
    }
}


#endif //NOALLOC_H
