#ifndef INCLUDE_H
#define INCLUDE_H
#include <SFML/Graphics.hpp>

using namespace sf;

const double pi = 3.1415926535897;
const double G  = 6.6754e-17; // e-17 so kilometers can be used for r

const int DEADZONE = 20;

struct PlanetData
{
    double mass;
    int aphelion;
    int perihelion;
    int radius;
    double orbitalSpeed;
    Vector2i orbitCenter;
    int orbitalPeriod;
    int x;
    int y;
    Color color;
    int orbitingPlanetIndex = -1; //if this is a moon, what planet it is orbiting
};


struct DrawData
{
    RenderWindow* window;
    double zoom;
    Vector2i viewPos;
    int windowWidth;
    int windowHeight;
};

struct GravData
{
    double mass;
    int x;
    int y;
    int radius;
    Vector2f velocity;
};

#endif // INCLUDE_H
