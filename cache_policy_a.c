#include <stdlib.h>

#include "cache.h"

#define CACHE_CAPACITY 100

typedef struct {
    int rod_length;
    cut_result_t result;
} cache_entry_t;

static cache_entry_t cache[CACHE_CAPACITY];
static int cache_size = 0;

void cache_init(void) {
    cache_size = 0;
}

cut_result_t *cache_lookup(int rod_length) {
    int index = 0;

    for (index = 0; index < cache_size; index++) {
        if (cache[index].rod_length == rod_length) {
            // Found matching entry; return pointer.
            return &cache[index].result;
        }
    }

    return NULL;
}

void cache_store(int rod_length, const cut_result_t *result) {
    int index = 0;

    // Check for existing entry.
    for (index = 0; index < cache_size; index++) {
        if (cache[index].rod_length == rod_length) {
            // Already in cache, do not overwrite or re-insert.
            return;
        }
    }

    // If there's space, store it at the next open spot.
    if (cache_size < CACHE_CAPACITY) {
        cache[cache_size].rod_length = rod_length;
        cache[cache_size].result     = *result;
        cache_size++;
    } else {
        // Cache is full; replace the first entry (oldest policy).
        cache[0].rod_length = rod_length;
        cache[0].result     = *result;
    }
}
