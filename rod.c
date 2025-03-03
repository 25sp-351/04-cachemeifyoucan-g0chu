#include "rod.h"

#include <stdio.h>
#include <stdlib.h>

int read_pieces_from_file(piece_t *pieces, const char *filename) {
    FILE *file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {
        perror("Error opening pieces file");
        return 0;
    }

    int piece_count = 0;
    int length      = 0;
    int value       = 0;

    // Parse until we reach max capacity or the scan fails.
    while (piece_count < MAX_PIECES &&
           fscanf(file_ptr, "%d, %d", &length, &value) == 2) {
        if (length < MIN_LENGTH || length > MAX_LENGTH)
            continue;

        pieces[piece_count].length = length;
        pieces[piece_count].value  = value;
        piece_count++;
    }

    fclose(file_ptr);
    return piece_count;
}

int find_best_piece(const piece_t *pieces, int piece_count, int rod_length) {
    int best_index = -1;
    int best_value = 0;
    int index      = 0;

    for (index = 0; index < piece_count; index++) {
        if (pieces[index].length <= rod_length) {
            int count       = rod_length / pieces[index].length;
            int total_value = count * pieces[index].value;
            if (total_value > best_value) {
                best_value = total_value;
                best_index = index;
            }
        }
    }

    return best_index;
}

cut_result_t process_rod_cutting(int rod_length, piece_t *pieces,
                                 int piece_count) {
    cut_result_t result;

    // Initialize result fields.
    result.rod_length   = rod_length;
    result.count        = 0;
    result.piece_length = 0;
    result.total_value  = 0;
    result.remainder    = rod_length;

    // Find the best piece for the given rod length.
    int best_index = find_best_piece(pieces, piece_count, rod_length);
    if (best_index == -1)
        return result;  // Return as is if no piece fits.

    int count           = rod_length / pieces[best_index].length;
    int total_value     = count * pieces[best_index].value;

    result.count        = count;
    result.piece_length = pieces[best_index].length;
    result.total_value  = total_value;
    result.remainder    = rod_length - (count * pieces[best_index].length);

    return result;
}

void print_cut_result(const cut_result_t *result) {
    if (result->count == 0) {
        printf("No valid pieces for rod length %d.\n", result->rod_length);
    } else {
        printf("%d @ %d = %d\n", result->count, result->piece_length,
               result->total_value);
        if (result->remainder > 0)
            printf("Remainder: %d\n", result->remainder);
    }
}
