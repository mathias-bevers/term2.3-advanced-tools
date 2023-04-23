#pragma once

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

        std::tuple<double, std::string> GetScaledTime(bool allLaps = false)
        {
            double elapsedMicro = (allLaps) ? stopwatch.elapsed_laps<microseconds>().first : stopwatch.lap<microseconds>();
            double elapsedMilli = elapsedMicro / 1000.0;
            double elapsedSec = elapsedMilli / 1000.0;

            if (elapsedSec >= 1)
            {
                return {elapsedSec, "s"};
            }

            if (elapsedMilli >= 1)
            {
                return {elapsedMilli, "ms"};
            }

            return {elapsedMicro, "\xE6s"};
        }

        std::string FormatMeasuredMessage(std::string message, double value, std::string measurement)
        {
            int padding = 55;
            std::stringstream sstream;
            sstream << std::fixed << std::setprecision(2) << value;
            if (message.length() + sstream.str().length() > padding)
            {
                std::cout << "FAILED TO FORMAT (message is too long): " << message << ":" << message.length();
                return "\n\nNULL";
            }

            std::string result = message.append(padding - message.length() - sstream.str().length(), ' ');
            result.append(sstream.str());
            result = result.append(padding + 5 - result.length(), ' ');
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