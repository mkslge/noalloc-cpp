#include <vector>
#include "../noalloc.h"

void testNonScopeAllocation() {
    //should not count towards allocations
    int* arr = new int[100];
    delete [] arr;

}


int main() {
    noalloc guard{noalloc_mode::log};
    testNonScopeAllocation();

    return 0;
}