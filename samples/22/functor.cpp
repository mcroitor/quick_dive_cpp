#include <iostream>

int square(int x) {
    return x * x;
}

struct _square2
{
  int operator ()(int x) {return x * x;}   
};

bool is_negative(int x) {
    return x < 0;
}

int main()
{
    int a = 4;
    _square2 square2;
    std ::cout <<"Square (" << a << ") = " << square2 (a);
    return 0; 
}

