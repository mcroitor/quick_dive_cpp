#include <iostream>
#include <string>

template <class type>
type sum(type a, type b)
{
    return a + b;
}

struct Integer{
    int value;
};

int main()
{
    std::cout << sum(1, 2) << std::endl;
    std::cout << sum(1.1, 2.2) << std::endl;
    std::cout << sum<double>(1, 2.2) << std::endl;
    std::cout << sum<std::string>("Hello, ", "world!") << std::endl;

    Integer a = {1};
    Integer b = {2};
    Integer c = sum(a, b);

    std::cout << c.value << std::endl;
    return 0;
}