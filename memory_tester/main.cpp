#include <iostream>
#include "src/tester.h"

int main()
{
    advanced_tools::Tester tester;
    tester.run();

    std::cout << "Press enter to exit...";
    std::cin.ignore();
}