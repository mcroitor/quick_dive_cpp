#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

bool isEven(int x) {
    return x % 2 == 0;
}

int main() {
    std::vector<int> v;
    std::copy(
      std::istream_iterator<int>(std::cin),
      std::istream_iterator<int>(),
      std::back_inserter(v));
    
    std::copy_if(
      v.begin(),
      v.end(),
      std::ostream_iterator<int>(std::cout, " "),
      isEven);
    return 0;
}