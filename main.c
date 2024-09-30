#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "collatz.h"
#include "config.h"
#include "cache.h"

unsigned long long rand_between(unsigned long long min, unsigned long long max) {
    return min + (rand() % (max - min + 1));
}

int main(int argc, char *argv[]) {
    srand(time(NULL));  // uses time as an int to get random seeding

    config_t *config = config_init(argc, argv);
    if (config == NULL) {
        return 1;
    }

    // initialize the cache with the specified size and policy
    cache_init(config->cache_size, config->cache_policy);

    unsigned max_steps = 0;
    
    for (unsigned i = 0; i < config->sample_count; i++) {
        unsigned long long rando = rand_between(config->range_min, config->range_max);

        unsigned steps = collatz_r(rando);

        if (steps > max_steps) {
            printf("Count: %d       Number: %llu new max %u\n", i, rando, steps);
            max_steps = steps;
        }
    }

    printf("Final max: %u\n", max_steps);
    printf("Cache hit rate: %.2f%%\n", cache_hit_rate() * 100);

    cache_free();
    config_free(config);

    return 0;
}
