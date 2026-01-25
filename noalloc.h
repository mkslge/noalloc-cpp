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




#endif //NOALLOC_H
