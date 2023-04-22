#pragma once
#include <list>
#include <string>
#include <sstream>

#include "TestingObject.hpp"

using namespace std;

namespace AdvancedTools
{
    /// @brief A class with an ID and a list of ints, the list is the size of the sample size. Which makes the it N to the power of N.
    class LargeObject : public TestingObject
    {
      public: 
        int id;
        list<int*> contents;

        public:
        LargeObject(int id, int sampleSize);
        ~LargeObject() override;

        string to_string() const override
        {            
            std::ostringstream ss;
            ss << "large#" << id << " with size of: " << sizeof(contents) + ((contents.size() + 1) * sizeof(int*));
            return ss.str();
        }
    };
}