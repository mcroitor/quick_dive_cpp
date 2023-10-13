#ifndef _TUI_H_
#define _TUI_H_

#include "point.hpp"
#include <vector>
#include <string>

struct TUI {
    static int ScanKeys();
    static void SetCursor(Point);
    static void Draw(const std::vector<std::string>&);
};

#endif