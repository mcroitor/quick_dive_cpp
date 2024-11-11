#include <iostream>
#include <map>

int main()
{
    std::map<std::string, int> direct = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}};
    std::map<int, std::string> inverse = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
    std::string first, second;
    std::cin >> first >> second;

    int a = direct[first];
    int b = direct[second];
    std::cout << first << " + " << second << " = " << inverse[a+b] << std::endl;
    return 0;
}
