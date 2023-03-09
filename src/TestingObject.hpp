#pragma once
#include <string>

namespace AdvancedTools
{
    class TestingObject
    {
    public:
        TestingObject(){};
        virtual ~TestingObject(){};
        virtual std::string to_string() const { return ""; }
    };
}