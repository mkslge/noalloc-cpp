# noalloc README.md

A tiny, header-only RAII guard that **checks for heap allocations inside a scope**.

`noalloc` is useful for making sure code paths dont allocate memory on accident

---

## Usage

### Terminate on allocation (default)

```cpp
#include "noalloc.h"

void hot_path() {
    noalloc guard; // will terminate if any heap allocation happens

    // code in scope must not allocate
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
