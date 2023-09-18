#include "gamecharacter.hpp"

GameCharacter::GameCharacter(std::string name): 
    _name(name), _attack(10), _health(100), _defence(2)
{
}
void GameCharacter::Move(direction_t direction)
{
    switch (direction) {
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

MapPart GameCharacter::ViewRange()
{
}

void GameCharacter::Attack(GameCharacter & gameCharacter)
{
    gameCharacter._health -= (this->_attack - gameCharacter._defence);
}