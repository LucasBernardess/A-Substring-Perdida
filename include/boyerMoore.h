#ifndef BOYERMOORE_H
#define BOYERMOORE_H

#define NO_OF_CHARS 256

void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS]);
int max(int a, int b);
void boyer_moore_with_indices(char *text, char *pattern, int num_intervals, int intervals[][2]);

#endif
