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

        TestSmall();
        uint64_t elapsed = stopwatch.lap();
        cout << "Completed small objects in " << elapsed << "ms" << endl;

        TestLarge();
        elapsed = stopwatch.lap();
        cout << "Completed large objects in " << elapsed << "ms" << endl;

        pair<uint64_t, vector<uint64_t>> laps = stopwatch.elapsed_laps();
        cout << "Completed test in " << laps.first << "ms" << endl;
    }

    void Tester::TestSmall()
    {
        Stopwatch localStopwatch;

        for (size_t i = 0; i < sampleSize; ++i)
        {
            testingObjects.push_back(new SmallObject(i));
        }
        cout << testingObjects.back()->to_string() << endl;
    }

    void Tester::TestLarge()
    {
        Stopwatch localStopwatch;
        localStopwatch.start();

        for(size_t i = 0; i < sampleSize; ++i)
        {
            testingObjects.push_back(new LargeObject(i, sampleSize));
        }

        cout << testingObjects.back()->to_string() << endl;
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