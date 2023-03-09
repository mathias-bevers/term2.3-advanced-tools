#pragma once
#include <string>
#include <sstream>

#include "TestingObject.hpp"

using namespace std;
namespace AdvancedTools
{
    /// @brief A class with just an id which makes the N.
    class SmallObject : public TestingObject
    {
    public:
        int *integer;

    public:
        SmallObject(int index);
        ~SmallObject() override;

        string to_string() const override
        {
            std::ostringstream ss;
            ss << "small#" << *integer << " with size of: " << sizeof(int*);
            return ss.str();
        }
    };
}