#include "Tester.hpp"

namespace AdvancedTools
{
    Tester::Tester(int sampleSize)
    {
        this->sampleSize = sampleSize;   
    }

    void Tester::Run()
    {
        cout << "Running test with " << sampleSize << " iterations." << endl << endl;

        stopwatch.start();
        
        uint64_t elapsedMS = TestSmall();
        cout << "Completed smallObjects in " << elapsedMS << "ms" << endl;

        
        cout << "Completed test in " << stopwatch.elapsed() << "ms" << endl;
    }

    uint64_t Tester::TestSmall()
    {
        Stopwatch localStopwatch;

        for (size_t i = 0; i < sampleSize; ++i)
        {
            testingObjects.push_back(new SmallObject(i));
        }
        cout << "Size of \'smallObject\': " << sizeof(testingObjects.end()) << endl;
        return localStopwatch.elapsed();
    }

    Tester::~Tester()
    {
        stopwatch.start();

        while (!testingObjects.empty())
        {
            delete testingObjects.front();
            testingObjects.pop_front();
        }

        cout << "cleaned up in " << stopwatch.elapsed() << " ms" << endl;
    }
}