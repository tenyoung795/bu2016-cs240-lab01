#ifndef LAB01TESTSUITE_H
#define LAB01TESTSUITE_H

#include "Lab01.h"
#include <TestSuite.h>
#include <ostream>
#include <utility>
#include <mutex>

template <class A, class B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}

class Lab01TestSuite: public ConcurrentTestSuite<>
{
    static mutex coutMutex;
    static Lab01 lab;

    public:
    Lab01TestSuite() noexcept;
};

#endif
