#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "cache.h"
#include "config.h"

typedef struct {
    uint64_t key;
    uint64_t value;
} 
cache_entry_t;

static cache_entry_t *cache = NULL;
static unsigned cache_size = 0;
static unsigned cache_count = 0;
static unsigned cache_hits = 0;
static unsigned cache_lookups = 0;
static cache_policy_t cache_policy;

// keep track of the next position
static unsigned fifo_pos = 0;

// using an array to track usage order
static unsigned *lru_order = NULL;

void cache_init(unsigned long size, cache_policy_t policy) {
    cache_size = size;
    cache_policy = policy;
    cache = malloc(size * sizeof(cache_entry_t));
    if (policy == CACHE_LRU) {
        lru_order = malloc(size * sizeof(unsigned));
        for (unsigned i = 0; i < size; i++) {
            lru_order[i] = i;
        }
    }
}

static void lru_update_order(unsigned index) {
    unsigned temp = lru_order[index];
    for (unsigned i = index; i > 0; i--) {
        lru_order[i] = lru_order[i - 1];
    }
    lru_order[0] = temp;
}

bool is_in_cache(uint64_t candidate) {
    cache_lookups++;
    for (unsigned i = 0; i < cache_count; i++) {
        if (cache[i].key == candidate) {
            cache_hits++;
            if (cache_policy == CACHE_LRU) {
                lru_update_order(i);
            }
            return true;
        }
    }
    return false;
}

uint64_t cache_value_for(uint64_t candidate) {
    for (unsigned i = 0; i < cache_count; i++) {
        if (cache[i].key == candidate) {
            return cache[i].value;
        }
    }
    return 0;
}

void cache_insert(uint64_t candidate, uint64_t value) {
    if (cache_count < cache_size) {
        cache[cache_count].key = candidate;
        cache[cache_count].value = value;
        cache_count++;
    } else {
        unsigned index = (cache_policy == CACHE_FIFO) ? fifo_pos : lru_order[cache_size - 1];
        cache[index].key = candidate;
        cache[index].value = value;
        if (cache_policy == CACHE_FIFO) {
            fifo_pos = (fifo_pos + 1) % cache_size;
        } else {
            lru_update_order(cache_size - 1);
        }
    }
}

float cache_hit_rate(void) {
    return (cache_lookups == 0) ? 0.0f : (float)cache_hits / cache_lookups;
}

void cache_free(void) {
    free(cache);
    if (cache_policy == CACHE_LRU) {
        free(lru_order);
    }
}
