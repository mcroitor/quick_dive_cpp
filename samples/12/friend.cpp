#include <iostream>

/**
 * @brief This class hides a secret number
 * But we can access it using a friend function
 */
class SuperSecuredClass
{
    /**
     * @brief The secret number
     */
    int secretNumber;

public:
    /**
     * @brief Construct a new Super Secured Class object
     * 
     * @param secretNumber The secret number
     */
    SuperSecuredClass(int secretNumber) : secretNumber(secretNumber) {}

    friend void printSecretNumber(const SuperSecuredClass &obj);
};

void printSecretNumber(const SuperSecuredClass &obj)
{
    int cout = 10;
    std::cout << "this is " << obj.secretNumber << std::endl;
}

template<typename T>
T min(T a, T b){
    return a < b ? a : b;
}

wchar_t char8;
char16_t char16;
char32_t char32; 

int main()
{
    SuperSecuredClass obj(42);
    printSecretNumber(obj);

    return 0;
}
