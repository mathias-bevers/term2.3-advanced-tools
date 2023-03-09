#include <iostream>
#include <list>

#include "src/Tester.hpp"

using namespace AdvancedTools;

// TODO: add argument support.
int main(int argc, char *argv[])
{
    int sampleSize = 10;

    if (argc > 1)
    {
        std::cout << "Cannot run with more than one argument, which is the sampleSize" << std::endl;
        return 1;
    }

    Tester* tester = new Tester(sampleSize);
    tester->Run();
    delete tester;

    std::cout << endl << endl <<"Press enter to exit...";
    std::cin.ignore();
    return 0;
}