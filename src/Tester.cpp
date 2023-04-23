#include "Tester.hpp"

namespace AdvancedTools
{
    Tester::Tester()
    {
        std::cout << "Initialized tester..." << std::endl;
    }

    void Tester::Run(int sampleSize)
    {
        std::stringstream sstream;
        std::tuple<double, std::string> scaledTime;

        sstream << "Running test with " << sampleSize << " iterations.";
        std::cout << std::endl <<std::string(65, '-')  << sstream.str() << std::endl;
        sstream.str(std::string());

        stopwatch.start();

        TestSmall(sampleSize);
        scaledTime = GetScaledTime();
        sstream << "Completed " << testingObjects.back()->to_string() << " in";
        std::cout << FormatMeasuredMessage(sstream.str(), std::get<0>(scaledTime), std::get<1>(scaledTime)) << std::endl;
        sstream.str(std::string());

        TestLarge(sampleSize);
        scaledTime = GetScaledTime();
        sstream << "Completed " << testingObjects.back()->to_string() << " in";
        std::cout << FormatMeasuredMessage(sstream.str(), std::get<0>(scaledTime), std::get<1>(scaledTime)) << std::endl;
        sstream.str(std::string());

        scaledTime = GetScaledTime(true);
        sstream << "Completed test in";
        std::cout << FormatMeasuredMessage(sstream.str(), std::get<0>(scaledTime), std::get<1>(scaledTime)) << std::endl;


        std::cout << FormatMeasuredMessage("Memory in use", GetUsedMemoryMB(), "MB") << std::endl;
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
        std::string timeScale;
        auto scaledTime = GetScaledTime();
        std::cout << FormatMeasuredMessage("Cleared list in", std::get<0>(scaledTime), std::get<1>(scaledTime));
    }

    Tester::~Tester() { std::cout << "\nDeleting tester..." << std::endl; }
}