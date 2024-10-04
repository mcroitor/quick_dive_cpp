#include <iostream>

// using namespace std;
using std::cout;

enum oops {
    oops1,
    oops2,
};

enum class text_color_type: char
{
    black = 30,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white,
    bright_black = 90,
    gray = text_color_type::bright_black,
    bright_red,
    bright_green,
    bright_yellow,
    bright_blue,
    bright_magenta,
    bright_cyan,
    bright_white,
};

// const int no_color = 20;
// int white = 30;

text_color_type int_to_color(int color)
{
    // check if the color is in the range of the enum
    if ((
            color >= static_cast<int>(text_color_type::black) && 
            color <= static_cast<int>(text_color_type::white)
        ) || (
            color >= static_cast<int>(text_color_type::bright_black) &&
            color <= static_cast<int>(text_color_type::bright_white)
        ))
    {
        return static_cast<text_color_type>(color);
    }
    return text_color_type::white;
}

int main()
{
    oops var = oops1; // oops::oops1;
    text_color_type myColor = text_color_type::white; // color_type::no_color;

    text_color_type bad_code = text_color_type::black;

    cout << "oops: " << var << std::endl;
    cout << "myColor: " << (int)myColor << std::endl;
    cout << "bad_code: " << (int)bad_code << std::endl;

    int color = 0;
    std::cin >> color;

    myColor = int_to_color(color);

    return 0;
}