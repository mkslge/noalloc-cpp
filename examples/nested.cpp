//
// Created by Mark on 1/26/26.
//

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
    {
        noalloc guard{noalloc_mode::log};
        int* arr =  new int[100];
        {
            int* arr1 =  new int[100];
            int* arr2 =  new int[100];
            int* arr3 =  new int[100];
        }
    }
    return 0;
}