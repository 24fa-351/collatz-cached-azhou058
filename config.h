#ifndef CONFIG_H
#define CONFIG_H

typedef enum {
    CACHE_NONE,
    CACHE_LRU,
    CACHE_FIFO
} cache_policy_t;

typedef struct {
    unsigned sample_count;
    unsigned long long range_min;
    unsigned long long range_max;
    unsigned cache_size;
    cache_policy_t cache_policy;
} config_t;

config_t *config_init(int argc, char *argv[]);
void config_free(config_t *config);

#endif
