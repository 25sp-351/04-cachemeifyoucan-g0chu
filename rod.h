#ifndef ROD_H
#define ROD_H

#define MAX_PIECES 100
#define MAX_LENGTH 1000
#define MIN_LENGTH 1

typedef struct {
    int length;
    int value;
} piece_t;

typedef struct {
    int rod_length;  // Input rod length.
    int count;       // Number of pieces.
    int piece_length;
    int total_value;
    int remainder;
} cut_result_t;

// Reads pieces from a file. The file should contain one pair per line in the
// format "length, value". Returns the number of valid pieces read.
int read_pieces_from_file(piece_t *pieces, const char *filename);

// Returns index of the best piece (using a greedy value-maximization).
int find_best_piece(const piece_t *pieces, int piece_count, int rod_length);

// Computes the cutting result for a given rod length using the provided pieces.
cut_result_t process_rod_cutting(int rod_length, piece_t *pieces,
                                 int piece_count);

// Prints the cutting result in the format: "count @ piece_length = total_value"
void print_cut_result(const cut_result_t *result);

#endif
