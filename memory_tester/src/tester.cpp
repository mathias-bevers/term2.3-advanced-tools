#include "tester.h"

#include <sys/time.h>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "../libraries/json.hpp"

namespace advanced_tools {

    STREAM_TYPE Tester::a[STREAM_ARRAY_SIZE];
    STREAM_TYPE Tester::b[STREAM_ARRAY_SIZE];
    STREAM_TYPE Tester::c[STREAM_ARRAY_SIZE];

    Tester::Tester()
    {
        printf(H_LINE);
        printf("Initializing tester v0.1\n");
        printf("This system uses %d bytes per array element.\n", bytes_per_word);
    }

    double Tester::get_second()
    {
        struct timeval tp;
        struct timezone tzp;

        gettimeofday(&tp, &tzp);
        return ((double) tp.tv_sec + (double) tp.tv_usec * 1.e-6);
    }

    int Tester::checktick()
    {
        const int n = 20;
        int i, min_delta, delta;
        double t1, t2, times_found[n];

        for (i = 0; i < n; ++i) {
            t1 = get_second();
            while (((t2 = get_second()) - t1) < 1.0E-6) {
                times_found[i] = t1 = t2;
            }
        }

        min_delta = 1000000;
        for (i = 0; i < n; ++i) {
            delta = (int) (1.0E6 * (times_found[i] - times_found[i - 1]));
            min_delta = std::min(min_delta, std::max(delta, 0));
        }

        return min_delta;
    }

    void Tester::check_configurations()
    {
        printf(H_LINE);
        printf("Initializing tester...\n");
        printf(H_LINE);
        printf("\tArray size = %d\n", STREAM_ARRAY_SIZE);
        printf("\tMemory per array = %.1f MiB (= %.1f GiB).\n", bytes_per_word * mib_per_word,
               bytes_per_word * gib_per_word);
        printf("\tTotal memory required = %.1f MiB (= %.1f GiB).\n", (3.0 * bytes_per_word) * mib_per_word,
               (3.0 * bytes_per_word) * gib_per_word);
        printf("\tEach kernel will be executed %d times.\n", ITERATIONS);

        for (size_t i = 0; i < STREAM_ARRAY_SIZE; ++i) {
            a[i] = 1.0;
            b[i] = 2.0;
            c[i] = 3.0;
        }

        int quantum;
        if ((quantum = checktick()) >= 1) {
            printf("\tYour clock granularity/precision appears to be %d microseconds.\n", quantum);
        } else {
            printf("\tYour clock granularity appears to be less than one microsecond.\n");
            quantum = 1;
        }

        double t = get_second();
        for (double& i: a) {
            i = 2.0E0 * i;
        }
        t = 1.0E6 * (get_second() - t);
        printf(H_LINE);
        printf("\tEach test will take on the order of %d microseconds. (%d clock ticks)\n", (int) t,
               (int) (t / quantum));
        printf("\tIncrease the size of the arrays if this shows that "
               "you are not getting at least 20 clock ticks per test.\n");
    }

    std::string Tester::generate_summary(double(& times)[4][ITERATIONS])
    {
        std::ofstream file_steam("full_results.json");
        nlohmann::json json;
        double total_time = 0;

        for (int i = 1; i < ITERATIONS; ++i) {
            std::string iteration_name = "iteration_" + std::to_string(i);
            for (int ii = 0; ii < 4; ++ii) {
                OperationSummary& summary = summaries[ii];
                json[iteration_name][summary.label] = times[ii][i];

                summary.average_time = summary.average_time + times[ii][i];
                summary.min_time = std::min(summary.min_time, times[ii][i]);
                summary.max_time = std::max(summary.max_time, times[ii][i]);
                total_time += times[ii][i];
            }
        }

        json["total_time"] = total_time;

        file_steam << json;
        file_steam.close();


        std::stringstream sstream;
        for (int i = 0; i < 4; ++i) {
            OperationSummary& summary = summaries[i];
            summary.average_time = summary.average_time / (double) (ITERATIONS - 1);
            summary.mb_per_second = 1.0E-6 * bytes[i] / summary.min_time;


            sstream << std::fixed << std::setprecision(2);
            sstream << "\t" << summary.label << ":\t";
            sstream << " average: " << summary.average_time;
            sstream << " min: " << summary.min_time;
            sstream << " max: " << summary.max_time;
            sstream << " peak MB/s: " << summary.mb_per_second;
            sstream << std::endl;
        }

        sstream << "\ttotal time to complete test: " << total_time << " seconds.";
        sstream << std::endl;
        return sstream.str();
    }

    void Tester::run()
    {
        check_configurations();
        printf(H_LINE);
        printf("Running tests...\n");

        double times[4][ITERATIONS];
        STREAM_TYPE scalar = 3.0;

        for (int i = 0; i < ITERATIONS; ++i) {
            times[0][i] = get_second();

            // ----------------------------------------------------- COPY
            for (int ii = 0; ii < STREAM_ARRAY_SIZE; ++ii) {
                c[ii] = a[ii];
            }

            times[0][i] = get_second() - times[0][i];
            times[1][i] = get_second();
            // ----------------------------------------------------- SCALE
            for (int ii = 0; ii < STREAM_ARRAY_SIZE; ++ii) {
                b[ii] = scalar * c[ii];
            }

            times[1][i] = get_second() - times[1][i];
            times[2][i] = get_second();
            // ----------------------------------------------------- ADD
            for (int ii = 0; ii < STREAM_ARRAY_SIZE; ++ii) {
                c[ii] = a[ii] + b[ii];
            }

            times[2][i] = get_second() - times[2][i];
            times[3][i] = get_second();
            // ----------------------------------------------------- TRIAD
            for (int ii = 0; ii < STREAM_ARRAY_SIZE; ++ii) {
                a[ii] = b[ii] + scalar * c[ii];
            }

            times[3][i] = get_second() - times[3][i];
        }

        std::string summary = generate_summary(times);
        printf("%s", summary.c_str());

        printf(H_LINE);
        printf("Test completed!\n");
    }

    Tester::~Tester()
    {
        printf(H_LINE);
        printf("Deleting tester...\n");
    }


} // advanced_tools