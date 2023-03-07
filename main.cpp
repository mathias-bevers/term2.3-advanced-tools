#include <iostream>
#include <list>

#include "src/Tester.hpp"

using namespace AdvancedTools;

// TODO: add argument support.
int main(int argc, char *argv[])
{
    int sampleSize = 10000;

    if (argc > 1)
    {
        std::cout << "Cannot run with more than one argument, which is the sampleSize" << std::endl;
        return 1;
    }

    Tester tester = Tester(sampleSize);
    tester.Run();

    std::cout << "Press enter to exit...";
    std::cin.ignore();
    return 0;
}