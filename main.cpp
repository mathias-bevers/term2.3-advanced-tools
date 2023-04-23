#include <iostream>
#include <string>
#include <list>

#include "src/plugins/MemoryInfo.hpp"
#include "src/plugins/cpuinfo.hpp"
#include "src/Tester.hpp"

using namespace AdvancedTools;

std::string GetSystemInfo()
{
    std::stringstream sstream;

    CPUInfo cpuInfo;
    sstream << "CPU: " << cpuInfo.model() << std::endl; 

    smbios::MemoryInfo memoryInfo;
    sstream << "RAM: " << memoryInfo.get_memory_info();

    return sstream.str();
}

int main(int argc, char *argv[])
{

    std::cout << GetSystemInfo() << std::endl; 

    std::list<int> sampleSizes{10, 100, 1000, 5000};
    Tester *tester = new Tester();

    if (argc >= 2)
    {
        sampleSizes.clear();

        for (int i = 1; i < argc - 1; ++i)
        {
            try
            {
                int sampleSize = std::stoi(argv[i]);

                if (sampleSize <= 0)
                {
                    throw new std::out_of_range("A sample size needs to be bigger than zero!");
                }

                sampleSizes.push_back(sampleSize);
            }
            catch (const std::invalid_argument &exception)
            {
                std::cout << argv[i] << "cannot be casted to an int!";
            }
            catch (const std::out_of_range &exception)
            {
                std::cout << argv[1] << "\t" << exception.what();
            }
        }
    }

    for (const int &sampleSize : sampleSizes)
    {
        tester->Run(sampleSize);
    }

    delete tester;

    std::cout << "\n\nPress enter to exit...";
    std::cin.ignore();
    return 0;
}