#ifndef TESTER
#define TESTER

#include <list>
#include "TestingObject.hpp"
#include "SmallObject.hpp"

namespace AdvancedTools
{
    class Tester
    {
    private:
        int sampleSize;
        std::list<TestingObject *> testingObjects;
        uint64_t elapsedMS;

    public:
        Tester(int sampleSize);

        void Run();

        ~Tester();
    };
}
#endif