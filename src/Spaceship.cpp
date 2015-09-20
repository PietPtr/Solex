#include "Spaceship.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

Vector2f globalToDrawCoords(Vector2i viewPos, Vector2i global, double zoom);

Spaceship::Spaceship()
{
    velocity = Vector2f(0, 0);
    position = Vector2i(10000000, 10000000);
}

void Spaceship::update(Time dt, std::vector<GravData>* gravData)
{
    Vector2f Fgrav(0, 0);
    gravForces.clear();

    for (int i = 0; i < gravData->size(); i++)
    {
        Vector2f planetGrav(0, 0);
        float distance = sqrt(pow(position.x - gravData->at(i).x, 2) + pow(position.y - gravData->at(i).y, 2));
        double Fplanetgrav = -G * ((mass * gravData->at(i).mass) / (pow(distance, 2)));
        planetGrav.x = Fplanetgrav * (position.x - gravData->at(i).x);
        planetGrav.y = Fplanetgrav * (position.y - gravData->at(i).y);
        std::cout << planetGrav.x << " " << planetGrav.y << "\n";
        gravForces.push_back(planetGrav);
    }
    std::cout << "\n";

    position.x += velocity.x * dt.asSeconds();
    position.y += velocity.y * dt.asSeconds();
}

void Spaceship::draw(DrawData drawData)
{
    RenderWindow* window = drawData.window;
    double zoom = drawData.zoom;
    Vector2i viewPos = drawData.viewPos;

    for (int i = 0; i < gravForces.size(); i++)
    {
        Vertex grav[] =
        {
            Vertex(globalToDrawCoords(viewPos, position, zoom)),
            Vertex(globalToDrawCoords(viewPos, position, zoom) + Vector2f(gravForces.at(i).x / 250.0, gravForces.at(i).y / 250.0))
        };
        grav[0].color = Color::Green;
        grav[1].color = Color::Green;
        window->draw(grav, 2, Lines);
    }
}
