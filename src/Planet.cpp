#include <iostream>
#include "Planet.h"
#include <SFML/Graphics.hpp>

using namespace sf;

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

void Planet::update(double simtime)
{
    int amplitude = (aphelion + perihelion) / 2;
    float angularFrequency = 2 * pi / orbitalPeriod;

    x = orbitCenter.x + amplitude * cos(angularFrequency * simtime);
    y = orbitCenter.y + amplitude * sin(angularFrequency * simtime);
}

void Planet::draw(RenderWindow* window, double zoom)
{
    double drawSize = radius / zoom; //draw size in pixels

    if ((int)drawSize <= 1)
    {
        RectangleShape planet;
        planet.setPosition(Vector2f(x / zoom, y / zoom));
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
        planet.setPosition(Vector2f(x / zoom, y / zoom));
        planet.setRadius(drawSize);
        planet.setFillColor(color);
        window->draw(planet);
    }
    std::cout << x / zoom << " " << y / zoom << ", r: " << drawSize << "\n";
}





