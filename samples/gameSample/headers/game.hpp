#ifndef _GAME_H_
#define _GAME_H_

#include "map.hpp"
#include "hero.hpp"
#include "monster.hpp"

#include <vector>
#include <string>

class Game {
    Map map;
    Hero hero;
    std::vector<Monster> monsters;

    const std::vector<std::string> Data() const;

public:
    Game();
    void Init(const std::string&);
    void Run();
};

#endif // _GAME_H_