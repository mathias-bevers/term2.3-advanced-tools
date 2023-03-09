#include "LargeObject.hpp"

namespace AdvancedTools
{
    LargeObject::LargeObject(int id, int sampleSize)
    {
        this->id = id;

        for (int i = 0; i < sampleSize; ++i)
        {
            contents.push_back(new int(i));
        }
    }

    LargeObject::~LargeObject()
    {
        while (!contents.empty())
        {
            delete contents.front();
            contents.pop_front();
        }
    }
}