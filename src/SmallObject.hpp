#pragma once

#include <string>
#include <sstream>

#include "TestingObject.hpp"

namespace AdvancedTools
{
    class SmallObject : public TestingObject
    {
    public:
        int *integer;

    public:
        SmallObject(int index);
        ~SmallObject() override;

        operator std::string() const
        {
            std::ostringstream stringStream;
            stringStream << "small#" << integer << " with size of: " << sizeof(this);
            return stringStream.str();
        }
    };
}