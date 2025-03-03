#include <stdlib.h>

#include "cache.h"

#define CACHE_CAPACITY 100

typedef struct {
    int rod_length;
    cut_result_t result;
} cache_entry_t;

static cache_entry_t cache[CACHE_CAPACITY];
static int cache_size = 0;

static void move_to_front(int index) {
    if (index == 0)
        return;

    cache_entry_t temp = cache[index];
    int loop_index     = 0;

    // Start at index and shift all entries to the right.
    for (loop_index = index; loop_index > 0; loop_index--)
        cache[loop_index] = cache[loop_index - 1];
    cache[0] = temp;
}

void cache_init(void) {
    cache_size = 0;
}

cut_result_t *cache_lookup(int rod_length) {
    int index = 0;

    for (index = 0; index < cache_size; index++) {
        if (cache[index].rod_length == rod_length) {
            // Mark as most recently used by moving to the front.
            move_to_front(index);
            return &cache[0].result;
        }
    }

    return NULL;
}

void cache_store(int rod_length, const cut_result_t *result) {
    int index = 0;

    // Check rod_length already exists in the cache.
    for (index = 0; index < cache_size; index++) {
        if (cache[index].rod_length == rod_length) {
            // Update the existing entry's result.
            cache[index].result = *result;
            // Move that entry to the front (most recently used).
            move_to_front(index);
            return;
        }
    }

    // If not found, either insert or evict.
    if (cache_size < CACHE_CAPACITY) {
        // There is space to insert new entry at front.
        int loop_index = 0;
        for (loop_index = cache_size; loop_index > 0; loop_index--)
            cache[loop_index] = cache[loop_index - 1];
        cache[0].rod_length = rod_length;
        cache[0].result     = *result;
        cache_size++;
    } else {
        // Cache is full; shift all entries by one and place new at front.
        int loop_index = 0;
        for (loop_index = CACHE_CAPACITY - 1; loop_index > 0; loop_index--)
            cache[loop_index] = cache[loop_index - 1];
        cache[0].rod_length = rod_length;
        cache[0].result     = *result;
    }
}
