#include "SmallObject.hpp"

namespace AdvancedTools
{
    SmallObject::SmallObject(int index)
    {
        integer = new int(index);
    }

    SmallObject::~SmallObject()
    {
        delete integer;
    }
}