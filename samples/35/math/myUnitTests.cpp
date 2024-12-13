#include "mymath.h"
#include <cassert>
#include <iostream>

int fail_count = 0;
int total_count = 0;
int test_count = 0;

bool MY_ASSERT(bool expression, std::string message = "")
{
    total_count++;
    if (!expression)
    {
        fail_count++;
        std::cerr << "Assertion failed: " << message << std::endl;
        return false;
    }
    return true;
}

void test_min()
{
    test_count++;
    MY_ASSERT(my::min(5, -10) == 10, "my::min(5, -10) == 10");
    MY_ASSERT(my::min(-5, 10) == -5, "my::min(-5, 10) == -5");
    MY_ASSERT(my::min(5, 10) == 5, "my::min(5, 10) == 5");
}

void test_mod()
{
    test_count++;
    MY_ASSERT(my::mod(5) == 5, "my::mod(5) == 5");
    MY_ASSERT(my::mod(-5) == 5, "my::mod(-5) == 5");
    MY_ASSERT(my::mod(0) == 0, "my::mod(0) == 0");
}

int main()
{
    test_min();
    test_mod();

    std::cout << "Tests run: "
              << test_count
              << ", Assertions: "
              << total_count
              << ", Failures: "
              << fail_count
              << std::endl;
    return fail_count;
}