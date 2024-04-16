#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "src/tester.h"

const char path_seperator =
#ifdef _WIN32
                            '\\';
#else
                            '/';
#endif

std::string get_executable_name(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result.back();
}

int main(int argc, char **argv)
{
    std::string file_name = get_executable_name(argv[0], path_seperator);
    file_name.erase(0, file_name.find_first_not_of("at"));
    file_name.erase(file_name.find_last_not_of(".exe") + 1);
    std::cout << file_name << std::endl;

    advanced_tools::Tester tester(file_name);
    tester.run();

    std::cout << "Press enter to exit...";
    std::cin.ignore();
}