#include <iostream>
#include "Planet.h"
#include "include.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int randint(int low, int high);
Vector2f globalToDrawCoords(Vector2i viewPos, Vector2i global, double zoom);

Planet::Planet(PlanetData data)
{
    mass = data.mass;
    aphelion = data.aphelion;
    perihelion = data.perihelion;
    radius = data.radius;
    orbitalSpeed = data.orbitalSpeed;
    orbitCenter = data.orbitCenter;
    orbitalPeriod = data.orbitalPeriod;
    x = 0;
    y = 0;
    color = data.color;
    phase = randint(0, orbitalPeriod);
    std::cout << phase << "\n";
}

void Planet::setData(PlanetData data)
{
    mass = data.mass;
    aphelion = data.aphelion;
    perihelion = data.perihelion;
    radius = data.radius;
    orbitalSpeed = data.orbitalSpeed;
    x = data.x;
    y = data.y;
}

void Planet::update(double simtime, double timeSpeed)
{
    int amplitude = (aphelion + perihelion) / 2;
    float angularFrequency = 2 * pi / (orbitalPeriod / timeSpeed);

    x = orbitCenter.x + amplitude * cos(angularFrequency * (simtime / timeSpeed + phase));
    y = orbitCenter.y + amplitude * sin(angularFrequency * (simtime / timeSpeed + phase));

    velocity.x = x - prevPos.x;
    velocity.y = y - prevPos.y;

    prevPos = Vector2i(x, y);

    /*Vector2f acceleration;
    /*Vector2f Fgrav;
    float distance = sqrt(pow(x, 2) + pow(y, 2));
    double Fplanetgrav = -G * ((mass * 1.98855e30) / (pow(distance, 2)));
    Fgrav.x = Fplanetgrav * (x / distance);
    Fgrav.y = Fplanetgrav * (y / distance);

    float distance = sqrt(pow(x, 2) + pow(y, 2));

    acceleration.x = sin()
    acceleration.y =

    velocity.x += acceleration.x;
    velocity.y += acceleration.y;

    x += velocity.x * simtime;
    y += velocity.y * simtime;
    std::cout << Fplanetgrav << " " << y << "\n";*/
}

void Planet::draw(RenderWindow* window, double zoom, Vector2i viewPos)
{
    double drawSize = radius / zoom; //draw size in pixels

    Vector2f drawPosition = globalToDrawCoords(viewPos, Vector2i(x, y), zoom);

    if ((int)drawSize <= 1)
    {
        RectangleShape planet;
        planet.setPosition(drawPosition);
        if (Keyboard::isKeyPressed(Keyboard::V))
            planet.setSize(Vector2f(100, 100));
        else
            planet.setSize(Vector2f(1, 1));
        planet.setFillColor(color);
        window->draw(planet);
    }
    else
    {
        CircleShape planet;
        planet.setPointCount(1024);
        planet.setPosition(drawPosition);
        planet.setRadius(drawSize);
        planet.setFillColor(color);
        planet.setOrigin(radius / zoom, radius / zoom);
        window->draw(planet);
    }
    //std::cout << x / zoom << " " << y / zoom << ", r: " << drawSize << "\n";
}





