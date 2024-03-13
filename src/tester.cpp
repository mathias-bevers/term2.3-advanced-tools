#include "tester.h"

#include <utility>
#include <iostream>

namespace advanced_tools {
    Tester::Tester(std::string message) : message(std::move(message)) {
        std::cout << "Initializing tester..." << std::endl;
    }

    void Tester::run() {
        std::cout << message << std::endl;
    }

    Tester::~Tester() {
        std::cout << "Deleting tester..." << std::endl;
    }


} // advanced_tools