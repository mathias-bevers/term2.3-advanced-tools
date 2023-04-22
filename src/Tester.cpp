#include "Tester.hpp"

namespace AdvancedTools
{
    Tester::Tester()
    {
        cout << "Initialized tester..." << endl;
    }

    void Tester::Run(int sampleSize)
    {
        stringstream sstream;
        tuple<uint64_t, string> scaledTime;

        sstream << "Running test with " << sampleSize << " iterations.";
        cout << endl << string(65, '-')  << sstream.str() << endl;
        sstream.str(string());

        stopwatch.start();

        TestSmall(sampleSize);
        scaledTime = GetScaledTime();
        sstream << "Completed " << testingObjects.back()->to_string() << " in";
        cout << FormatMeasuredMessage(sstream.str(), get<0>(scaledTime), get<1>(scaledTime)) << endl;
        sstream.str(string());

        TestLarge(sampleSize);
        scaledTime = GetScaledTime();
        sstream << "Completed " << testingObjects.back()->to_string() << " in";
        cout << FormatMeasuredMessage(sstream.str(), get<0>(scaledTime), get<1>(scaledTime)) << endl;
        sstream.str(string());

        scaledTime = GetScaledTime(true);
        sstream << "Completed test in";
        cout << FormatMeasuredMessage(sstream.str(), get<0>(scaledTime), get<1>(scaledTime)) << endl;


        cout << FormatMeasuredMessage("Memory in use", GetUsedMemoryMB(), "MB", true) << endl;
        CleanList();
    }

    void Tester::TestSmall(int &sampleSize)
    {
        for (size_t i = 0; i < sampleSize; ++i)
        {
            testingObjects.push_back(new SmallObject(i));
        }
    }

    void Tester::TestLarge(int &sampleSize)
    {
        for (size_t i = 0; i < sampleSize; ++i)
        {
            testingObjects.push_back(new LargeObject(i, sampleSize));
        }
    }

    void Tester::CleanList()
    {
        stopwatch.start();

        while (!testingObjects.empty())
        {
            delete testingObjects.front();
            testingObjects.pop_front();
        }

        uint64_t elapsed;
        string timeScale;
        auto scaledTime = GetScaledTime();
        cout << FormatMeasuredMessage("Cleared list in", get<0>(scaledTime), get<1>(scaledTime));
    }

    Tester::~Tester() { cout << "\nDeleting tester..." << endl; }
}