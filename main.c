#include <stdio.h>
#include <stdlib.h>

#include "cache.h"
#include "rod.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <pieces_file>\n", argv[0]);
        return 1;
    }

    piece_t pieces[MAX_PIECES];
    int piece_count = read_pieces_from_file(pieces, argv[1]);

    if (piece_count == 0) {
        printf("No valid pieces inputted from file %s.\n", argv[1]);
        return 1;
    }

    // Initialize caching system (with policy A or B).
    cache_init();

    // Repeatedly read candidate rod lengths from stdin.
    int rod_length = 0;
    while (scanf("%d", &rod_length) == 1) {
        // Check if rod length's result is cached.
        cut_result_t *cached_result = cache_lookup(rod_length);

        if (cached_result != NULL) {
            // Cache hit: just print.
            print_cut_result(cached_result);
        } else {
            // Compute and store the result.
            cut_result_t result =
                process_rod_cutting(rod_length, pieces, piece_count);
            print_cut_result(&result);
            cache_store(rod_length, &result);
        }
    }

    return 0;
}
