#include <iostream>
#include "Planet.h"
#include <SFML/Graphics.hpp>

Planet::Planet(PlanetData data)
{
    mass = data.mass;
    aphelion = data.aphelion;
    perihelion = data.perihelion;
    radius = data.radius;
    orbitalSpeed = data.orbitalSpeed;
    x = data.x;
    y = data.y;
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

void Planet::update()
{
    //Vector2f velocity;
    double Fgrav = 1;
    double r = sqrt(pow(aphelion, 2) + pow(0, 2)) * 1000; // in meters
    double m1 = mass;
    double m2 = 1.98855e30;
    double G = 6.6754e-11;

    //std::cout << r << " " << aphelion << "\n";

    std::cout << "r: " << r << "\nm1: " << m1 << "\nm2: " << m2 << "\nG: " << G;

    if (r > 0)
        Fgrav = G * ((m1 * m2) / pow(r, 2));

    std::cout << "\nFgrav: " << Fgrav << "\n";
}
