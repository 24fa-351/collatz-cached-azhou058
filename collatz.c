#include "collatz.h"
#include "cache.h"

unsigned collatz_r(uint64_t candidate) {
    if (candidate == 1) {
        return 0;  // base case
    }
    
    //check if result in cache
    if (is_in_cache(candidate)) {
        return cache_value_for(candidate);
    }

    uint64_t new_candidate;
    if (candidate % 2 == 0) {
        new_candidate = candidate / 2;
    } else {
        new_candidate = 3 * candidate + 1;
    }

    // calculate the Collatz steps for the new candidate
    unsigned count = 1 + collatz_r(new_candidate);

    cache_insert(candidate, count);

    return count;
}
