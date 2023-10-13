#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "gamecharacter.hpp"

class Monster : public GameCharacter
{
public:
    Monster(const std::string& = "Monster", Point = {1, 1});
};

#endif