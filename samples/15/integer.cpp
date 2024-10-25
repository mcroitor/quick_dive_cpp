#include <iostream>

class Integer
{
    int value;

public:
    Integer() = default;
    Integer(int value) : value(value) {}
    Integer(const Integer &i) : value(i.value) {}
    int GetValue() const { return value; }
};

int operator<=>(const Integer &i1, const Integer &i2)
{
    if (i1.GetValue() < i2.GetValue()) {
        return -1;
    } else if (i1.GetValue() > i2.GetValue()) {
        return 1;
    } else {
        return 0;
    }
}

bool operator==(const Integer &i1, const Integer &i2)
{
    return i1.GetValue() == i2.GetValue();
}
int main()
{
    Integer i(5);

    if (i == 5)
    { // operator==(i, 5)
        std::cout << "i == 5" << std::endl;
    }
    else
    {
        std::cout << "i != 5" << std::endl;
    }

    if (5 == i)
    { // operator==(5, i)
        std::cout << "5 == i" << std::endl;
    }
    else
    {
        std::cout << "5 != i" << std::endl;
    }

    i < 6;
    return 0;
}

// a + b + c == (a + b) + c == a + (b + c)
// a + b == b + a