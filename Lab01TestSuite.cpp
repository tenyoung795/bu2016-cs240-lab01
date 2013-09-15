#include "Lab01TestSuite.h"
#include "Lab01.h"

#include <Assert.h>
#include <iostream>
#include <ostream>
#include <sstream>
#include <climits>
#include <type_traits>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <mutex>
#include <future>
#include <stdexcept>

using namespace std;

mutex Lab01TestSuite::coutMutex;

class temporarilyRedirectCout // exploits RAII to auto-restore buffer regardless of an exception
{
    streambuf *buf;
    public:
    temporarilyRedirectCout(const ostream &s): buf(cout.rdbuf()) { cout.rdbuf(s.rdbuf()); }
    ~temporarilyRedirectCout() { cout.rdbuf(buf); }
};

Lab01TestSuite::Lab01TestSuite() noexcept: TestSuite(
{
    {"testQuestion1a", [](Lab01 &lab)
    {
		static int empty[]{};
		static int singleton[]{0};
		static int regularArray[]{0, 2, 4, 6, 8, 7, 5, 3, 1};
		static int maxFirst[]{8, 4, 2, 0, 1, 3, 5, 7};
        static int maxLast[]{0, 1, 2, 3, 4, 5, 6, 7, 8};
        static int lowSingleton[]{-10001};

		static const map<pair<int *, int>, int> testCases
		{
			{{nullptr, 1}, -10000},
			{{empty, 0}, -10000},
			{{singleton, 1}, singleton[0]},
			{{regularArray, extent<decltype(regularArray)>::value}, 8},
            {{regularArray, 4}, 6}, // incomplete array
			{{maxFirst, extent<decltype(maxFirst)>::value}, 8},
            {{maxLast, extent<decltype(maxLast)>::value}, 8},
            {{lowSingleton, 1}, lowSingleton[0]}
		};

		for (auto &testCase : testCases)
		{
			assertEquals(int,
				testCase.second, lab.question1a(testCase.first.first, testCase.first.second));
		}
	}},
	{"testQuestion2", [](Lab01 &lab)
	{
		static const map<pair<int, int>, vector<int>> testCases
		{
            // GCC can't confidently infer the value types
            {{0, -3}, vector<int>{0, -2}},
            {{0, -2}, vector<int>{0}},
            {{0, -1}, vector<int>{0}},
            {{0, 0}, vector<int>{}},
            {{0, 1}, vector<int>{0}},
            {{0, 2}, vector<int>{0}},
            {{0, 3}, vector<int>{0, 2}},
            {{1, -3}, vector<int>{0, -2}},
            {{1, -2}, vector<int>{0}},
            {{1, -1}, vector<int>{0}},
            {{1, 0}, vector<int>{}},
            {{1, 1}, vector<int>{}},
            {{1, 2}, vector<int>{}},
            {{1, 3}, vector<int>{2}},
            {{1, 4}, vector<int>{2}},
            {{1, 5}, vector<int>{2, 4}}
        };

        lock_guard<mutex> lock(coutMutex);
        stringstream s;
        auto tmp = temporarilyRedirectCout(s);
				
		for (auto &testCase : testCases)
        {
            lab.question2(testCase.first.first, testCase.first.second);
            string line;
            for (int expected : testCase.second)
            {
                assertTrue(getline(s, line));
                try
                {
                    assertEquals(int, expected, stoi(line));
                }
                catch (invalid_argument &e)
                {
                    fail(string("invalid_argument: ") + e.what());
                }
                catch (out_of_range &e)
                {
                    fail(string("out_of_range: ") + e.what());
                }
            }
            assertFalse(getline(s, line));
            
            s.str("");
            s.clear();
        }
	}},
    {"testQuestion3Quick", [](Lab01 &lab)
    {
        static const map<pair<int, int>, int> testCases
        {
            {{0, 1}, -1},
            {{1, 0}, -1},
            {{1, 2}, 2},
            {{2, 1}, 2},
            {{2, 3}, 6},
            {{3, 2}, 6}
        };

        for (auto &testCase : testCases)
        {
            assertEquals(int,
                testCase.second, lab.question3(testCase.first.first, testCase.first.second));
        }
    }},
    {"testQuestion3EdgePass1", [](Lab01 &lab)
    {
        assertEquals(int, INT_MAX, lab.question3(1, INT_MAX));

    }},
    {"testQuestion3EdgePass2", [](Lab01 &lab)
    {
        assertEquals(int, INT_MAX, lab.question3(INT_MAX, 1));

    }},
    {"testQuestion3EdgeFail1", [](Lab01 &lab)
    {
        assertEquals(int, -1, lab.question3(2, INT_MAX));

    }},
    {"testQuestion3EdgeFail2", [](Lab01 &lab)
    {
        assertEquals(int, -1, lab.question3(INT_MAX, 2));

    }},
    {"testQuestion4", [](Lab01 &lab)
    {
        static const map<string, string> testCases
        {
            {"", ""},
            {"a", "a"},
            {"bar", "rab"},
            {"bob", "bob"}
        };
        for (auto &testCase : testCases)
        {
            assertEquals(string, testCase.second, lab.question4(testCase.first));
        }
    }},
    {"testQuestion5", [](Lab01 &lab)
    {
        lock_guard<mutex> lock(coutMutex);
        stringstream s;
        auto tmp = temporarilyRedirectCout(s);

        lab.question5();
        
        string line;
        int expected;
        for (expected = 1; expected <= 100; expected++)
        {
            assertTrue(getline(s, line));

            bool multipleOfFour = expected % 4 == 0;
            bool multipleOfSeven = expected % 7 == 0;

            if (multipleOfFour && multipleOfSeven)
            {
                assertEquals(string, "FizzBuzz", line); 
            }
            else if (multipleOfFour)
            {
                assertEquals(string, "Fizz", line);
            }
            else if (multipleOfSeven)
            {
                assertEquals(string, "Buzz", line);
            }
            else
            {
                try
                {
                    assertEquals(int, expected, stoi(line));
                }
                catch (invalid_argument &e)
                {
                    fail(string("invalid_argument: ") + e.what());
                }
                catch (out_of_range &e)
                {
                    fail(string("out_of_range: ") + e.what());
                }
            }
        }
        // make sure 100 was the last number, so expected would be 101
        assertEquals(int, 101, expected);
        assertFalse(getline(s, line));
    }},
    {"testQuestion6", [](Lab01 &lab)
    {
        lock_guard<mutex> lock(coutMutex);
        stringstream s;
        auto tmp = temporarilyRedirectCout(s);

        lab.question6();
        
        assertEquals(string,
            "X\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\n"
            "1\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\n"
            "2\t2\t4\t6\t8\t10\t12\t14\t16\t18\t20\t22\t24\n"
            "3\t3\t6\t9\t12\t15\t18\t21\t24\t27\t30\t33\t36\n"
            "4\t4\t8\t12\t16\t20\t24\t28\t32\t36\t40\t44\t48\n"
            "5\t5\t10\t15\t20\t25\t30\t35\t40\t45\t50\t55\t60\n"
            "6\t6\t12\t18\t24\t30\t36\t42\t48\t54\t60\t66\t72\n"
            "7\t7\t14\t21\t28\t35\t42\t49\t56\t63\t70\t77\t84\n"
            "8\t8\t16\t24\t32\t40\t48\t56\t64\t72\t80\t88\t96\n"
            "9\t9\t18\t27\t36\t45\t54\t63\t72\t81\t90\t99\t108\n"
            "10\t10\t20\t30\t40\t50\t60\t70\t80\t90\t100\t110\t120\n"
            "11\t11\t22\t33\t44\t55\t66\t77\t88\t99\t110\t121\t132\n"
            "12\t12\t24\t36\t48\t60\t72\t84\t96\t108\t120\t132\t144\n",
            s.str());
    }}
}) {}

