#include <iostream>

class A
{
    int x;

public:
    A(int _x)
    {
        x = _x;
        std::cout << "A constructor, " << x << std::endl;
    }
    int getX() const { return x; }
};

class B
{
    A a;

public:
    B(int _x) : a(_x)
    {
        // a = A(_x);
        std::cout << "B constructor" << a.getX() << std::endl;
    }
};

class arr
{
    int *value;
    int size;

public:
    arr(int size): size(size), value(new int[size]) {
        for(int i = 0; i < size; ++i){
            value[i] = i;
        }
    }
    ~arr() {delete [] value; }

    int GetSize() const {
        return size;
    }

    int& operator [](int index){
        return value[index];
    }
    const int& operator [](int index) const{
        return value[index];
    }
};

int main()
{
    B b(2);

    arr a(10);

    for(int i = 0; i < a.GetSize(); ++i) {
        a[i] = i * i;
    }
    for(int i = 0; i < a.GetSize(); ++i) {
        std::cout << a[i];
    }
    return 0;
}