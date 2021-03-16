#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BILLION 1000000000L;

int main(int argc, char **argv)
{
    char command[] = "./run <cases_q1/X.in >cases_q1/X.out";
    int idx = 16;
    int idx2 = 31;
    for (int a = 0; a < 10; a++)
    {
        struct timespec start, stop;
        double accum;

        if (clock_gettime(CLOCK_REALTIME, &start) == -1)
        {
            perror("clock gettime");
            return 1;
        }
        command[idx] = command[idx2] = '0' + a;
        system(command);

        if (clock_gettime(CLOCK_REALTIME, &stop) == -1)
        {
            perror("clock gettime");
            return 1;
        }

        accum = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / (double)BILLION;
        printf("%lf\n", accum);
    }
    return 0;
}
