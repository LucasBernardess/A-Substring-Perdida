#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#define MAX_ALPHABET 256

void preprocessShift(char *pattern, int patternLength, int shiftTable[MAX_ALPHABET]);
void bmhWithIndices(char *text, char *pattern, int numberOfIntervals, int intervals[][2], FILE *outputFile);

#endif