#include <stdlib.h>
#include <string.h>
#include "config.h"
#include <stdio.h>

config_t *config_init(int argc, char *argv[]) {
    if (argc < 6) {
        printf("Usage: ./collatz <sample_count> <min> <max> <cache_size> <cache_policy>\n");
        return NULL;
    }

    config_t *config = malloc(sizeof(config_t));
    config->sample_count = strtoul(argv[1], NULL, 10);
    config->range_min = strtoull(argv[2], NULL, 10);
    config->range_max = strtoull(argv[3], NULL, 10);
    config->cache_size = strtoul(argv[4], NULL, 10);

    if (strcmp(argv[5], "none") == 0) {
        config->cache_policy = CACHE_NONE;
    } else if (strcmp(argv[5], "LRU") == 0) {
        config->cache_policy = CACHE_LRU;
    } else if (strcmp(argv[5], "FIFO") == 0) {
        config->cache_policy = CACHE_FIFO;
    } else {
        printf("Unknown cache policy: %s\n", argv[5]);
        free(config);
        return NULL;
    }

    return config;
}

void config_free(config_t *config) {
    free(config);
}
