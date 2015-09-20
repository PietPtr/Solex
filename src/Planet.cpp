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
    velocity = Vector2f(0, orbitalSpeed);
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
    //x = A cos(wt + f)
    //y = A sin(wt + f)
    int amplitude = (aphelion + perihelion) / 2;
    float angularFrequency = 2 * pi / orbitalPeriod;

    x = orbitCenter.x + amplitude * cos(angularFrequency * simtime);
    y = orbitCenter.y + amplitude * sin(angularFrequency * simtime);

    std::cout << (int)(x / 10e4) << " " << (int)(y / 10e4) << "\n";
    //std::cout << amplitude << "\n";
    //std::cout << angularFrequency << "\n";

}

void Planet::draw(RenderWindow* window)
{
    CircleShape px;
    px.setPosition(Vector2f(x / 50e4, y / 50e4));
    px.setRadius(1);
    px.setFillColor(Color(255, 255, 255));
    window->draw(px);
}





