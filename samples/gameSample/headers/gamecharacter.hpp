#ifndef __GAME_CHARACTER_H__
#define __GAME_CHARACTER_H__

#include <string>

#include "point.hpp"
#include "direction.hpp"
#include "mappart.hpp"

class GameCharacter {
    size_t      _attack;
    size_t      _defence;
    size_t      _health;
    std::string _name;
    Point       _position;
    size_t      _viewRangeRadius;

public:
  GameCharacter(std::string, Point); // конструктор
  void Move(Direction);
  Point PositionToMove(Direction) const;
  void Cure(size_t);
  MapPart ViewRange() const;
  Point Position() const;

  void Attack(GameCharacter&) const;
};

#endif // __GAME_CHARACTER_H__
