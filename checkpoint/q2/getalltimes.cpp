#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#define BILLION 1000000000L;

int main(int argc, char **argv)
{
    std::string x = "./run <Q2/t";
    std::string y = " >myout/";
    std::string z = ".out";
    std::string cases[] = {"6", "19", "29", "31", "43", "49", "75", "77", "78", "91"};

    std::string diffx = "diff ./Q2out/t";
    std::string diffy = " ./myout/";
    std::string diffz = ".out | wc -l";
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
        command = diffx + cases[a] + diffy + cases[a] + diffz;
        system(command.c_str());
    }
    return 0;
}
