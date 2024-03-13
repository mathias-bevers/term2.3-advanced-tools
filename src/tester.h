#ifndef ADVANCED_TOOLS_TESTER_H
#define ADVANCED_TOOLS_TESTER_H

#include <string>

namespace advanced_tools {

    class Tester {
    private:
        std::string message;

    public:
        Tester(std::string message);

        void run();

        ~Tester();
    };

} // advanced_tools

#endif //ADVANCED_TOOLS_TESTER_H
