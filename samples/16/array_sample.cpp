#include <iostream>
#include <cmath>

template <typename TYPE, int SIZE>
class array
{
    TYPE elements[SIZE];

public:
    TYPE operator[](int index) const
    {
        return elements[index];
    }
    TYPE &operator[](int index)
    {
        return elements[index];
    }
    int size() const
    {
        return SIZE;
    }

    typedef TYPE *iterator;
    typedef const TYPE *const_iterator;

    iterator begin()
    {
        return elements;
    }
    const_iterator begin() const
    {
        return elements;
    }

    iterator end()
    {
        return elements + SIZE;
    }
    const_iterator end() const
    {
        return elements + SIZE;
    }
};

template <typename TYPE, int SIZE>
typename array<TYPE, SIZE>::iterator begin(const array<TYPE, SIZE> &a)
{
    return a.begin();
}
template <typename TYPE, int SIZE>
typename array<TYPE, SIZE>::iterator end(const array<TYPE, SIZE> &a)
{
    return a.end();
}


template <typename TYPE, int SIZE>
TYPE array_sum(const array<TYPE, SIZE> &a)
{
    TYPE sum = TYPE();
    /*
    for(int i = 0; i < a.size(); ++i) {
        sum += a[i];
    }
    */
    for (auto el : a)
    {
        sum += el;
    }
    return sum;
}

int main()
{
    array<double, 10> a;

    for (int i = 0; i < a.size(); i++)
    {
        a[i] = sqrt(i);
    }

    for (int i = 0; i < a.size(); i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    double sum = array_sum(a);

    std::cout << "sum of elements: " << sum;
    return 0;
}