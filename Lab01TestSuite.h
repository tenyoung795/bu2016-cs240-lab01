#ifndef LAB01TESTSUITE_H
#define LAB01TESTSUITE_H

#include "Lab01.h"
#include <TestSuite.h>
#include <mutex>

class Lab01TestSuite: public TestSuite<Lab01>
{
    static mutex coutMutex;

    public:
    Lab01TestSuite() noexcept;
};

#endif
