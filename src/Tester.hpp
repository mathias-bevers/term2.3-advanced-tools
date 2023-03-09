#ifndef TESTER
#define TESTER

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <list>

#include "plugins/Stopwatch.hpp"
#include "TestingObject.hpp"
#include "SmallObject.hpp"
#include "LargeObject.hpp"

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
        void TestSmall();
        void TestMedium();
        void TestLarge();
    };
}
#endif