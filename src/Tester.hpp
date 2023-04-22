#ifndef TESTER
#define TESTER

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <string>
#include <windows.h>
#include <psapi.h>
#include <iomanip>
#include <tuple>

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
        std::list<TestingObject *> testingObjects;
        Stopwatch stopwatch;
        PROCESS_MEMORY_COUNTERS pmc;

    public:
        Tester();

        void Run(int sampleSize);

        ~Tester();

    private:
        void TestSmall(int &sampleSize);
        void TestLarge(int &sampleSize);

        void CleanList();

        tuple<uint64_t, string> GetScaledTime(bool allLaps = false)
        {
            uint64_t elapsedMilli;
            uint64_t elapsedMicro;

            if (allLaps)
            {
                elapsedMicro = stopwatch.elapsed_laps<microseconds>().first;
                elapsedMilli = (uint64_t)((elapsedMicro / 1000.0) + 0.5);
            }
            else
            {
                elapsedMicro = stopwatch.lap<microseconds>();
                elapsedMilli = (uint64_t)((elapsedMicro / 1000.0) + 0.5);
            }

            if (elapsedMilli < 1)
            {
                return {elapsedMicro, "\xE6s"};
            }

            return {elapsedMilli, "ms"};
        }

        string FormatMeasuredMessage(string message, double value, string measurement, bool decimalPrecision = false)
        {
            if (message.length() > 50)
            {
                cout << "FAILED TO FORMAT (message is too long): " << message << ":" << message.length();
                return "\n\nNULL";
            }

            stringstream sstream;
            sstream << fixed << setprecision(decimalPrecision ? 2 : 0) << value;

            string result = message.append(50 - message.length(), ' ');
            result.append(sstream.str());
            result = result.append(60 - result.length(), ' ');
            result.append(measurement);
            return result;
        }

        double GetUsedMemoryMB()
        {
            GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
            return static_cast<double>(pmc.WorkingSetSize) / static_cast<double>(1024 * 1024);
        }
    };
}
#endif