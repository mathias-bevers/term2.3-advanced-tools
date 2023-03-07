#include <iostream>

#include "Tester.hpp"
namespace AdvancedTools
{
    Tester::Tester(int sampleSize)
    {
        this->sampleSize = sampleSize;
    }

    void Tester::Run()
    {
        std::cout << "Run" << std::endl;

        for (size_t i = 0; i < sampleSize; ++i)
        {
            testingObjects.push_back(new SmallObject(i));
        }
    }

    Tester::~Tester()
    {
        while (!testingObjects.empty())
        {
            delete testingObjects.front();
            testingObjects.pop_front();
        }
    }
}