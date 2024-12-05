#include <iostream>
#include <vector>
#include <algorithm>

template <class IIter, class T>
IIter my_find(IIter first, IIter last, const T &val)
{
    while (first != last)
    {
        if (*first == val)
            return first;
        ++first;
    }
    return first;
}

template <class IIter, class pred>
IIter my_find_if(IIter first, IIter last, const pred &p)
{
    while (first != last)
    {
        if (p(*first))
            return first;
        ++first;
    }
    return first;
}

template <int divisor>
bool divizible(int x)
{
    return x % divisor == 0;
}

int main()
{
    std::vector<int> array{1, 3, 5, 7, 9};
    auto i = my_find(array.begin(), array.end(), 4);
    if (i == array.end())
        std::cout << "Not found" << std::endl;
    else
        std::cout << "Found " << *i << std::endl;
        
    i = my_find_if(array.begin(), array.end(), divizible<4>);
    if (i == array.end())
        std::cout << "Not found" << std::endl;
    else
        std::cout << "Found " << *i << std::endl;

    std::vector<int> result;

    std::copy_if(
        array.begin(),
        array.end(),
        std::back_inserter(result),
        divizible<3>);

    for(auto el: result) {
        std::cout << el << " ";
    }
    return 0;
}