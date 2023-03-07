#ifndef TESTER
#define TESTER

#include <list>
#include <iostream>
#include <string>

#include "plugins/Stopwatch.hpp"
#include "TestingObject.hpp"
#include "SmallObject.hpp"

using namespace std;
using namespace stopwatch;

namespace AdvancedTools
{
    class Tester
    {
    private:
        int sampleSize;
        std::list<TestingObject *> testingObjects;
        Stopwatch stopwatch;
    public:
        Tester(int sampleSize);

        void Run();

        ~Tester();

    private:
        uint64_t TestSmall();
        uint64_t TestMedium();
        uint64_t TestLarge();
    };
}
#endif