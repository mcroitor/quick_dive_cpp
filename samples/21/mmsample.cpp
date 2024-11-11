#include <iostream>
#include <map>
#include <string>

int main()
{
    std::multimap<std::string, std::string> direct = {
        {"GD2302", "Stanislav Hodarca"},
        {"GD2302", "Elena Suvalova"},
        {"GD2302", "Vadim Spanu"},
        {"GD2302", "Olga Misina"},
        {"GD2303", "Serghei Udaltov"}
    };

    for(auto elements: direct) {
        std::cout << elements.first << ": " << elements.second << std::endl;
    }
    return 0;
}
