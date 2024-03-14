#ifndef ADVANCED_TOOLS_TESTER_H
#define ADVANCED_TOOLS_TESTER_H

#include <string>
#include <cfloat>
#include "operation_summary.h"

#ifndef STREAM_TYPE
#define STREAM_TYPE double
#endif

#ifndef STREAM_ARRAY_SIZE
#   define STREAM_ARRAY_SIZE   625000000 // after some testing this requires around 14305.1 MiB of memory.
#endif

#ifndef ITERATIONS
#   define ITERATIONS 10
#endif

# define H_LINE "-------------------------------------------------------------\n"

namespace advanced_tools {
    class Tester {
    private:
        // these arrays need to be static to get a high capacity.
        static STREAM_TYPE a[STREAM_ARRAY_SIZE], b[STREAM_ARRAY_SIZE], c[STREAM_ARRAY_SIZE];

        OperationSummary summaries[4] = {
                {"copy", 0, DBL_MAX, 0, -1},
                {"scale", 0, DBL_MAX, 0, -1},
                {"add", 0, DBL_MAX, 0, -1},
                {"triad", 0, DBL_MAX, 0, -1},
        };


        STREAM_TYPE bytes[4] = {
                2 * sizeof(STREAM_TYPE) * STREAM_ARRAY_SIZE,
                2 * sizeof(STREAM_TYPE) * STREAM_ARRAY_SIZE,
                3 * sizeof(STREAM_TYPE) * STREAM_ARRAY_SIZE,
                3 * sizeof(STREAM_TYPE) * STREAM_ARRAY_SIZE
        };

        int bytes_per_word = sizeof(STREAM_TYPE);
        double mib_per_word = ((double) STREAM_ARRAY_SIZE / 1024.0 / 1024.0);
        double gib_per_word = ((double) STREAM_ARRAY_SIZE / 1024.0 / 1024.0 / 1024.0);

    public:
        Tester();

        double get_second();

        int checktick();

        std::string generate_summary(double (& times)[4][ITERATIONS]);

        void check_configurations();

        void run();

        ~Tester();
    };

} // advanced_tools

#endif //ADVANCED_TOOLS_TESTER_H
