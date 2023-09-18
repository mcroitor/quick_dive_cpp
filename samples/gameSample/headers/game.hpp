#ifndef _GAME_H_
#define _GAME_H_

#include "map.hpp"

class Game {
    Map map;

public:
    Game();
    void Run();
};

#endif // _GAME_H_