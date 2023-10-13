#include "tui.hpp"

#include <iostream>
#include <windows.h>
#include <WinUser.h>

int TUI::scanKeys()
{
    if (GetAsyncKeyState(VK_UP))
    {
        return VK_UP;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        return VK_DOWN;
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        return VK_LEFT;
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        return VK_RIGHT;
    }
    if (GetAsyncKeyState(VK_ESCAPE))
    {
        return VK_ESCAPE;
    }
    return VK_NONAME;
}

void TUI::setPosition(point_t position)
{
    std::cout << "\033[" << position.x << ";" << position.y << "H";
}

void TUI::Draw(const std::vector<std::string> &data)
{
    std::string output = "";
    for (auto line : data)
    {
        output += line + "\n";
    }
    std::cout << output << std::endl;
}