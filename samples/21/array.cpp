#include <iostream>

template<typename TYPE, size_t SIZE>
class Array {
    TYPE elements[SIZE];
public:
    typedef TYPE value_type;
    typedef TYPE* iterator;    
    typedef const TYPE* const_iterator;    

    Array(){}

    Array(const Array<TYPE>& a) {
        for(size_t i = 0; i < SIZE; ++i){
            elements[i] = a[i];
        }
    }

    ~Array(){}

    iterator begin(){
        return elements;
    }

    iterator end(){
        return elements + SIZE;
    }

    const_iterator begin() const{
        return elements;
    }

    const_iterator end() const{
        return elements + SIZE;
    }

    size_t size() const{
        return SIZE;
    }

    bool empty() const{
        return SIZE == 0;
    }

    TYPE front() const {
        return *(begin());
    }

    TYPE back() const {
        return *(--end());
    }

    TYPE& operator [](size_t index){
        return elements[index];
    }

    const TYPE& operator [](size_t index) const{
        return elements[index];
    }
};

using array = Array<int, 10>;

int main() {
    array arr;

    for(auto it = arr.begin(); it != arr.end(); ++it) {
        *it = 12;
    }
    return 0;
}