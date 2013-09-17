#ifndef LAB01TESTSUITE_H
#define LAB01TESTSUITE_H

#include "Lab01.h"
#include <TestSuite.h>
#include <ostream>
#include <utility>
#include <mutex>

template <class A, class B>
std::ostream &operator<<(std::ostream &os, const std::pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}

class Lab01TestSuite: public ConcurrentTestSuite<>
{
    static std::mutex coutMutex;
    static Lab01 lab;

    public:
    Lab01TestSuite() noexcept;
};

#endif
