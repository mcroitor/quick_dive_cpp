#ifndef __GAME_CHARACTER_H__
#define __GAME_CHARACTER_H__

#include <string>

#include "point.hpp"
#include "direction.hpp"
#include "mappart.hpp"

class GameCharacter {
    std::string _name;
    size_t      _health;
    size_t      _attack;
    size_t      _defence;
    size_t      _viewRangeRadius;
    point_t     _position;

public:
  GameCharacter(std::string); // конструктор
  void Move(direction_t);
  void Cure(size_t);
  MapPart ViewRange();

  void Attack(GameCharacter&);
};

#endif // __GAME_CHARACTER_H__
