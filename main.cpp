#include <iostream>
#include <list>
#include <sysinfoapi.h>
#include <string>

#include "src/Tester.hpp"
#include "src/plugins/cpuinfo.hpp"

using namespace AdvancedTools;

string GetSystemInfo()
{
    stringstream sstream;

    CPUInfo cpuInfo;
    sstream << "CPU: " << cpuInfo.model() << endl; 

    unsigned long long physicalMemoryKB = 0;
    GetPhysicallyInstalledSystemMemory(&physicalMemoryKB);
    double physicalMemoryGB =  physicalMemoryKB / 1024.0 / 1024.0;
    
    sstream << "RAM: ";
    sstream << fixed << setprecision(2) << physicalMemoryGB << " GB";
    sstream << endl << endl;


    return sstream.str();
}

int main(int argc, char *argv[])
{

    cout << GetSystemInfo() << endl; 

    list<int> sampleSizes{10, 100, 1000, 5000};
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
                    throw new out_of_range("A sample size needs to be bigger than zero!");
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