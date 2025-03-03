#ifndef CACHE_H
#define CACHE_H

#include "rod.h"

void cache_init(void);

// Looks up a cached cut result for the given rod length.
// Returns a pointer to the cached result if found, or NULL otherwise.
cut_result_t *cache_lookup(int rod_length);

void cache_store(int rod_length, const cut_result_t *result);

#endif
