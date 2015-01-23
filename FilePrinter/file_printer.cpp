// Cameron Bielstein, 1/22/15
// file_printer.cpp
// Takes input file(s) and prints them to the screen on loop, clearing between prints.
// Inserts sleeps for effect
// Originally writte for the Hill Country Middle School career fair, thus the included cougar ascii art :)

// cout
#include <iostream>

// read the file
#include <fstream>

// sleep!
#include <unistd.h>
#include <chrono>
#include <thread> // cross platform millisend sleep

// rand
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: file_printer <file 1> <file 2> ... <file n>" << std::endl
                  << "You didn't give any files!" << std::endl << "Debug: argc == "
                  << argc << std::endl;
        return -1;
    }

    // initialize random
    srand(time(NULL));

    // loop forever showing ascii art. It'll be so cool :)
    while (true)
    {
        // loop through each of the given files...
        // start at the first arg, since argv[0] is the program itself
        for (int i = 1; i < argc; ++i)
        {
            int ret_val = system("clear");
            if (ret_val == -1)
            {
                std::cout << "system() call failed." << std::endl;
                return -1;
            }

            // assume input is safe since I'm the only one running it
            std::ifstream in_file;
            in_file.open(argv[i]);
            if (in_file.fail())
            {
                std::cout << "Failed to open file " << argv[i] << std::endl;
                return -1;
            }

            // print bit-by-bit
            char c;
            while (in_file >> std::noskipws >> c)
            {
                // this is a cross platform sleep
                long int sleep_time = rand() % 100;
                std::chrono::milliseconds duration(sleep_time);
                std::this_thread::sleep_for(std::chrono::milliseconds(duration));
                std::cout << c;
                std::cout.flush();
            }

            in_file.close();
            sleep(5);
        }
    }
}
