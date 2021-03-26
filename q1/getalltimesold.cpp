#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#define BILLION 1000000000L;

int main(int argc, char **argv)
{
    std::string x = "./run </scratch/q1/A1/myQ1/";
    std::string y = ".in >/scratch/q1/A1/myQ1out/";
    std::string z = ".out";
    std::string cases[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    double total = 0;
    for (int a = 0; a < 15; a++)
    {
        struct timespec start, stop;
        double accum;

        if (clock_gettime(CLOCK_REALTIME, &start) == -1)
        {
            perror("clock gettime");
            return 1;
        }
        std::string command = x + cases[a] + y + cases[a] + z;
        system(command.c_str());

        if (clock_gettime(CLOCK_REALTIME, &stop) == -1)
        {
            perror("clock gettime");
            return 1;
        }

        accum = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / (double)BILLION;
        std::cout << command << "\n"
                  << accum << "\n";
        total += accum;
    }
    std::cout << "Total: " << total << "\n";
    return 0;
}
