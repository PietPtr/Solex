#include "Spaceship.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

Vector2f globalToDrawCoords(Vector2i viewPos, Vector2i global, double zoom);

Spaceship::Spaceship()
{
    velocity = Vector2f(0, 29.78);
    position = Vector2i(10000000, 10000000);
}

void Spaceship::update(double dt, std::vector<GravData>* gravData)
{
    Vector2f Fgrav(0, 0);
    gravForces.clear();

    for (int i = 0; i < gravData->size(); i++)
    {
        Vector2f planetGrav(0, 0);
        float distance = sqrt(pow(position.x - gravData->at(i).x, 2) + pow(position.y - gravData->at(i).y, 2));
        double Fplanetgrav = -G * ((mass * gravData->at(i).mass) / (pow(distance, 2)));
        planetGrav.x = Fplanetgrav * (position.x - gravData->at(i).x) / distance;
        planetGrav.y = Fplanetgrav * (position.y - gravData->at(i).y) / distance;
        gravForces.push_back(planetGrav);
        Fgrav += planetGrav;
    }

    Vector2f acceleration;

    acceleration.x = Fgrav.x / mass;
    acceleration.y = Fgrav.y / mass;

    velocity.x += acceleration.x;
    velocity.y += acceleration.y;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    std::cout << position.x * 1 << " " << position.y * 1 << "\n";
}

void Spaceship::draw(DrawData drawData)
{
    RenderWindow* window = drawData.window;
    double zoom = drawData.zoom;
    Vector2i viewPos = drawData.viewPos;

    for (int i = 0; i < gravForces.size(); i++)
    {
        float mod = 10e-4;
        Vertex grav[] =
        {
            Vertex(globalToDrawCoords(viewPos, position, zoom)),
            Vertex(globalToDrawCoords(viewPos, position, zoom) + Vector2f(gravForces.at(i).x / mod, gravForces.at(i).y / mod))
        };
        grav[0].color = Color::Green;
        grav[1].color = Color::Green;
        window->draw(grav, 2, Lines);
    }
}
