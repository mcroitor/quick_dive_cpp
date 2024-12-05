#include <vector>
#include <iostream>
#include <ranges>

int main() {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {6, 7, 8, 9, 10};

    auto joined = v1 | std::views::join(v2);

    joined | std::ranges::for_each([](int i) { std::cout << i << ' '; });
    std::cout << '\n';
    return 0;
}