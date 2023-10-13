#include <iostream>

template <typename TYPE>
class SmartPointer
{
    TYPE* ptr;

public:
    SmartPointer(TYPE* p): ptr(p){}
    ~SmartPointer() { delete ptr; }

    TYPE& operator*() const { return *ptr; }
    TYPE* operator->() const { return ptr; }
};

int main() {
    SmartPointer<int> ptr(new int {10});

    std::cout << *ptr << std::endl;
    return 0;
}