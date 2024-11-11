#include <iostream>

/**
 * f_n = f_(n-2) + f_(n-1)
 * f_0 = 0
 * f_1 = 1
 * f_2 = f_0 + f_1 = 1
 * f_3 = f_1 + f_2 = 2
 * ...
 * f_10 = f_8 + f_9
 */

template <int index>
int fibbonacci()
{
    return fibbonacci<index - 2>() + fibbonacci<index - 1>();
}

template <>
int fibbonacci<0>()
{
    return 0;
}

template <>
int fibbonacci<1>()
{
    return 1;
}

template<class T1, class T2>
struct is_same {
    enum {RESULT = 0};
};

template<class T>
struct is_same<T, T>
{
    enum {RESULT = 1};
};

int main()
{
    int result = fibbonacci<10>();
    std::cout << result << std::endl;

    std::cout << is_same<int, float>::RESULT << std::endl;
    std::cout << is_same<int, int>::RESULT << std::endl;

    return 0;
}

// fibbonacci<10>() --> fibbonacci<8>() + fibbonacci<9>()