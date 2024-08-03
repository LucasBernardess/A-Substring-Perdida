#include <stdio.h>
#include <string.h>
#include "boyerMoore.h"

void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS]) {
    int i;
    for (i = 0; i < NO_OF_CHARS; i++) {
        badchar[i] = -1;
    }
    for (i = 0; i < size; i++) {
        badchar[(int)str[i]] = i;
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void boyer_moore_with_indices(char *text, char *pattern, int num_intervals, int intervals[][2], FILE *outputFile) {
    int m = strlen(pattern);
    int n = strlen(text);
    int badchar[NO_OF_CHARS];
    badCharHeuristic(pattern, m, badchar);
    
    int match_positions[n];
    int match_count = 0;

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            match_positions[match_count++] = s;
            s += (s + m < n) ? m - badchar[(unsigned char)text[s + m]] : 1;
        } else {
            s += max(1, j - badchar[(unsigned char)text[s + j]]);
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