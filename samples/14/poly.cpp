#include <cstdio>

struct A
{
    A() {}
    virtual void print() const { puts("A"); }
};

struct B : public A
{
    B() {}
    void print() const { puts("B"); }
};

void print(A &a)
{
    a.print();
}

int main()
{
    B obj;
    print(obj);
    return 0;
}
