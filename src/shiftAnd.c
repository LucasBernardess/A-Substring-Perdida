#include <stdio.h>
#include <string.h>
#include "shiftand.h"

#define MAX_CHAR 256

void shift_and_with_indices(const char *text, const char *pattern, int num_intervals, int intervals[][2], FILE *outputFile) {
    int m = strlen(pattern);
    int n = strlen(text);
    uint32_t B[MAX_CHAR] = {0};
    uint32_t state = 0;
    int match_positions[n];
    int match_count = 0;

    for (int i = 0; i < m; i++) {
        B[(unsigned char)pattern[i]] |= (1 << i);
    }

    for (int i = 0; i < n; i++) {
        state = ((state << 1) | 1) & B[(unsigned char)text[i]];
        if (state & (1 << (m - 1))) {
            match_positions[match_count++] = i - m + 1;
        }
    }

    for (int k = 0; k < num_intervals; k++) {
        int start = intervals[k][0] - 1;
        int end = intervals[k][1] - 1;
        int found = 0;
        for (int i = 0; i < match_count; i++) {
            if (match_positions[i] >= start && match_positions[i] <= end - m + 1) {
                found = 1;
                break;
            }
        }
        if (found) {
            fprintf(outputFile, "sim\n");
        } else {
            fprintf(outputFile, "nao\n");
        }
    }
}
