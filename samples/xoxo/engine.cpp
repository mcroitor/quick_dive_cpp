#include "engine.h"
#include "coordonate.h"

Engine::Engine()
{
}

void Engine::Run()
{
    bool xMove = true;
    Coordonate move;
    while (!GameOver())
    {
        if (xMove)
        {
            move = xPlayer_.Move(board_);
        }
        else
        {
            move = oPlayer_.Move(board_);
        }
        xMove = !xMove;
        board_.DoMove(move);
    }
}

bool Engine::GameOver() const
{
    // TODO: implement
    return false;
}