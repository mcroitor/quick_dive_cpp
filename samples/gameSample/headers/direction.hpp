#ifndef _DIRECTION_H_
#define _DIRECTION_H_

#include <windows.h>
#include <WinUser.h>

enum class Direction {
  north = VK_UP,
  south = VK_DOWN,
  east = VK_RIGHT,
  west = VK_LEFT
};

#endif