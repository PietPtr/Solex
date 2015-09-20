#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

using namespace sf;
int main()
{
    srand(time(NULL));

    int windowWidth = 1600;
    int windowHeigth = 900;
    RenderWindow window(VideoMode(windowWidth, windowHeigth), "Float");
    window.setVerticalSyncEnabled(true);

    Game game(&window);

    game.initialize();

    while (window.isOpen())
    {
        game.update();
        game.draw();
    }

    return 0;
}

int randint(int low, int high, int seed)
{
    srand(seed);
    int value = rand() % (high + 1 - low) + low;
    return value;
}

int randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    srand(value * rand());

    return value;
}

Vector2f globalToDrawCoords(Vector2i viewPos, Vector2i global, double zoom)
{
    Vector2i difference = global - viewPos;
    Vector2f drawCoords;
    drawCoords.x = difference.x / zoom;
    drawCoords.y = difference.y / zoom;

    return drawCoords;
}
