#ifndef KMP_H
#define KMP_H

void kmpWithIndices(char *text, char *pattern, int numberOfIntervals, int intervals[][2], FILE *outputFile);
void buildFailureTable(char *pattern, int patternLength, int *failureTable);

#endif