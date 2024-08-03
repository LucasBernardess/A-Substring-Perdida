#ifndef TIME_H
#define TIME_H

#include <sys/time.h>
#include <sys/resource.h>

void calculateExecutionTime(struct timeval start, struct timeval end, struct rusage usageStart, struct rusage usageEnd);

#endif 
