# noalloc

A tiny, header-only RAII guard that **checks for heap allocations inside a scope**.

`noalloc` is useful for making sure critical code paths don’t accidentally allocate memory — for example in hot loops, real-time systems, or performance-sensitive code.

---

## Why use it?

Heap allocations can sneak in without you noticing:

- `std::vector` growth
- iostream usage
- lazy initialization in the STL
- accidental `new` calls

`noalloc` lets you catch these either by logging or terminating the program.

---

## Features

- RAII-based (scope guard)
- Thread-local allocation counting
- Detects `new` and `new[]`
- Minimal overhead when no allocations happen
- Configurable behavior: log or terminate
- No dependencies

---

## Usage

### Terminate on allocation (default)

```cpp
#include "noalloc.h"

void hot_path() {
    noalloc guard; // will terminate if any heap allocation happens

    // code here must not allocate
}
```

If a heap allocation happens while `guard` is alive, the program will terminate.


```cpp
#include "noalloc.h"
#include <vector>

void debug_path() {
    noalloc guard(noalloc_mode::log);

    std::vector<int> v; // allocation
}

```

Output:
`[noalloc] 1 allocation(s) occurred in scope.`
