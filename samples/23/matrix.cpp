// g++ matrix.cpp -o matrix -std=c++20
#include <array>
#include <iostream>
#include <thread>
#include <mutex>

using matrix = std::array<std::array<double, 4>, 4>;
std::mutex mutex;

void sum(const matrix &a, const matrix &b, matrix &c, int row)
{
    for (int i = 0; i < 4; i++)
    {
        c[row][i] = a[row][i] + b[row][i];
    }
}

void print(const matrix &m)
{
    std::lock_guard<std::mutex> locker(mutex);
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; ++col)
        {
            std::cout << m[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    matrix a{
        std::array<double, 4>{2, 3, 4, 1},
        std::array<double, 4>{1, 3, 2, 4},
        std::array<double, 4>{0, 3, 3, 0},
        std::array<double, 4>{4, 1, 1, 1},
    };
    matrix b{
        std::array<double, 4>{1, 3, 4, 1},
        std::array<double, 4>{1, 3, 0, 4},
        std::array<double, 4>{0, 4, 3, 0},
        std::array<double, 4>{4, 1, 2, 1},
    };
    matrix c{
        std::array<double, 4>{0, 0, 0, 0},
        std::array<double, 4>{0, 0, 0, 0},
        std::array<double, 4>{0, 0, 0, 0},
        std::array<double, 4>{0, 0, 0, 0},
    };

    {
        std::lock_guard<std::mutex> locker(mutex);
        std::jthread t1(sum, a, b, std::ref(c), 0);
        std::jthread t2(sum, a, b, std::ref(c), 1);
        std::jthread t3(sum, a, b, std::ref(c), 2);
        std::jthread t4(sum, a, b, std::ref(c), 3);
    }
    std::jthread tprint(print, c);
    // std::jthread tprint2(print, c);
    return 0;
}