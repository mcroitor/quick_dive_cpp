#include <iostream>

template<typename TYPE>
void swap(TYPE& p1, TYPE& p2) {
  TYPE tmp = p1;
  p1 = p2;
  p2 = tmp;
}

template<typename TYPE>
void swap(TYPE* p1, TYPE* p2) {
  TYPE tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}

template void swap(double&, double&);

int main() {
  double a = 10;
  double b = 12;

  double* p1 = &a;
  double* p2 = &b;
  std::cout << "*p1: " << *p1 << ", *p2: " << *p2 << std::endl;
// неявное инстанциирование
  swap(p1, p2);
  std::cout << "*p1: " << *p1 << ", *p2: " << *p2 << std::endl;
  return 0;
}