#include <vector>
#include "../noalloc.h"

int main() {
    {
        noalloc guard{noalloc_mode::log};

        int *arr = new int[10];
    }
    return 0;
}