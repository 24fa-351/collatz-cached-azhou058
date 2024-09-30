#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>
#include <stdint.h>
#include "config.h"

void cache_init(unsigned long size_of_cache, cache_policy_t policy);

bool is_in_cache(uint64_t candidate);
uint64_t cache_value_for(uint64_t candidate);
void cache_insert(uint64_t candidate, uint64_t value);

void cache_free(void);
float cache_hit_rate(void);

#endif
