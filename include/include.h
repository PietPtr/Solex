#ifndef INCLUDE_H
#define INCLUDE_H
#include <SFML/Graphics.hpp>

using namespace sf;

const double pi = 3.1415926535897;

struct PlanetData
{
    double mass;
    int aphelion;
    int perihelion;
    double radius;
    double orbitalSpeed;
    Vector2i orbitCenter;
    int orbitalPeriod;
    int x;
    int y;
    Color color;
};


struct DrawData
{
    RenderWindow* window;
    double zoom;
    Vector2i viewPos;
};

#endif // INCLUDE_H
