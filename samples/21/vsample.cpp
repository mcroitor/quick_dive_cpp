#include <iostream>
#include <deque>
int main()
{
    std::deque<int> v = {1, 2, 3, 4, 5};

    v.push_back(6);
    v[2] = 33;

    v.pop_front();
    for (int el : v)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    return 0;
}
