#pragma once

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
    };
}