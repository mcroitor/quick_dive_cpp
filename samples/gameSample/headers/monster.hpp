#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "gamecharacter.hpp"

class Monster : public GameCharacter
{
public:
    Monster(const std::string& = "Monster", point_t = {1, 1});
};

#endif