#include "Lab01TestSuite.h"
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
	bool success = Lab01TestSuite{}();
	return success? EXIT_SUCCESS : EXIT_FAILURE;
}

