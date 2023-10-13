#ifndef _HERO_H_
#define _HERO_H_

#include "gamecharacter.hpp"

class Hero : public GameCharacter
{
public:
    Hero(const std::string& = "Hero", Point = {1, 1});
};

#endif