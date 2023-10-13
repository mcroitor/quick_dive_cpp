#include "gamecharacter.hpp"

GameCharacter::GameCharacter(std::string name, point_t position)
    : _attack(10),
      _defence(2),
      _health(100),
      _name(name),
      _position(position),
      _viewRangeRadius(3)
{
}

void GameCharacter::Move(direction_t direction)
{
    switch (direction)
    {
    case direction_t::north: // top
        _position.x -= 1;
        break;
    case direction_t::south: // bottom
        _position.x += 1;
        break;
    case direction_t::east: // right
        _position.y += 1;
        break;
    case direction_t::west: // left
        _position.y -= 1;
        break;
    }
}
void GameCharacter::Cure(size_t value)
{
    _health += value;
}

MapPart GameCharacter::ViewRange() const
{
    return MapPart();
}

void GameCharacter::Attack(GameCharacter &gameCharacter) const
{
    size_t damage = 0;
    if (this->_attack >= gameCharacter._defence)
    {
        damage = this->_attack - gameCharacter._defence;
    }
    if (gameCharacter._health >= damage)
    {
        gameCharacter._health -= gameCharacter._health - damage;
    }
    else
    {
        gameCharacter._health = 0;
    }
}

point_t GameCharacter::Position() const
{
    return _position;
}