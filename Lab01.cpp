#include "Lab01.h"

#include <string>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int Lab01::question1a(int array[], int arraySize)
{
    if (array == nullptr || arraySize <= 0)
    {
        return -10000;
    }

    int max = array[0];
    for (int i = 1; i < arraySize; i++)
    {
        if (array[i] > max) max = array[i];
    }
    return max;
}

void Lab01::question2(int start, int finish)
{
	if (start <= finish)
	{
		// If start is odd, then add 1
		for (int i = start + start % 2; i < finish; i += 2)
		{
			cout << i << '\n';
		}
	}
	else
	{
		// If start is odd, then subtract 1
		for (int i = start - start % 2; i > finish; i -= 2)
		{
			cout << i << '\n';
		}
	}
}

int Lab01::question3(int first, int second)
{
    // lcm(a, b) = (a * b) / gcd(a, b) 
    // gcd(a, a) = a
    // gcd(a, b) = gcd(a - b, b) if a > b else gcd(a, b - a)

    // although 0 makes sense for LCM, the contract specifies positive integers
    if (first <= 0 || second <= 0) return -1;

    static const auto gcd = [](int a, int b)
    {
        while (true)
        {
            if (a == b) return a;
            if (a > b) a -= b;
            else b -= a;
        }
    };
    
    int dividedSecond = second /= gcd(first, second); // divide then multiply to reduce overflow
    if (dividedSecond > INT_MAX / first) return -1; // still do overflow check
    return first * dividedSecond;
}

string Lab01::question4(string the_string)
{
    return string(the_string.crbegin(), the_string.crend());
}

void Lab01::question5()
{
    for (int i = 1; i <= 100; i++)
    {
        bool multipleOfFour = i % 4 == 0;
        bool multipleOfSeven = i % 7 == 0;
        if (multipleOfFour && multipleOfSeven)
        {
            cout << "FizzBuzz\n";
        }
        else if (multipleOfFour)
        {
            cout << "Fizz\n";
        }
        else if (multipleOfSeven)
        {
            cout << "Buzz\n";
        }
        else
        {
            cout << i << '\n';
        }
    }
}

void Lab01::question6()
{
    // upper-left corner
    cout << 'X';

    // rest of the top row
    for (int c = 1; c <= 12; c++)
    {
        cout << '\t' << c;
    }
    cout << '\n';

    // rest of the rows
    for (int r = 1; r <= 12; r++)
    {
        // leftmost column
        cout << r;

        // rest of the columns in row
        for (int c = 1, product = r; c <= 12; c++, product += r)
        {
            cout << '\t' << product;
        }

        cout << '\n';
    }
}

