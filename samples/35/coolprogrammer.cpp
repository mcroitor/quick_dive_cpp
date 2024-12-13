#include <SFML/Graphics.hpp>
#include "figure.h"
#include "game.h"
#include "clear.h"
#include "field.h"

using namespace sf;

const std::string BIG_TEXT = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                             "Duis gravida iaculis felis. Nunc ut eleifend turpis. Duis "
                             "risus odio, pharetra non finibus et, congue sit amet diam. "
                             "Proin libero ante, pharetra sit amet risus a, aliquam "
                             "accumsan lacus. Pellentesque pharetra augue nec lectus "
                             "varius, blandit ornare augue ullamcorper. Cras dapibus "
                             "non sem at fringilla. Nam venenatis consectetur orci "
                             "vitae finibus. Suspendisse pellentesque erat non lectus "
                             "viverra fringilla. Aenean vel libero volutpat, sollicitudin "
                             "elit nec, porttitor quam.";

const int SPRITE_SIZE = 18;
const int TOTAL_SPRITES = 4;

/**
 * @brief Create base field.
 *        After refactoring.
 * @param window 
 * @param sprite
 * @return int status
 */
int ClearField(RenderWindow &window, const Sprite &sprite) {
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (field[i][j] == 0)
            {
                continue;
            }
            s.setTextureRect(IntRect(field[i][j] * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
            s.setPosition(j * SPRITE_SIZE, i * SPRITE_SIZE);
            window.draw(s);
        }
    }
    return 0;
}

/// <summary>
/// Set sprites on the field.
/// </summary>
void SetSprites(RenderWindow &window, const Sprite &sprite) {
    for (int i = 0; i < TOTAL_SPRITES; i++)
    {
        s.setTextureRect(IntRect(colorNum * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
        s.setPosition(a[i].x * SPRITE_SIZE, a[i].y * SPRITE_SIZE);
        window.draw(s);
    }
}

void DrawField(RenderWindow &window, Sprite &s)
{
    ClearField(window, s);

    SetSprites(window, s);
}

int main()
{
    RenderWindow window(VideoMode(320, 480), "Tetris");

    Texture t;
    t.loadFromFile("images/tiles.png");
    Sprite s(t);

    int dx = 0;
    bool rotate = false;
    float timer = 0,
          delay = 0.3;
    Clock clock;
    int colorNum = 1;

    generateNewFigure();

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        handleInput(window, dx, rotate);
        updateGameState(window, dx, rotate, timer, delay, colorNum);

        clearFullLines();

        window.clear(Color::White);
        DrawField(window, s);

        window.display();
    }

    return 0;
}