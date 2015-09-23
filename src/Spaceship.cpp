#include "Spaceship.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

Vector2f globalToDrawCoords(Vector2i viewPos, Vector2i global, double zoom);

Spaceship::Spaceship(std::vector<Texture>* _textures)
{
    textures = _textures;
    velocity = Vector2f(0, -100);
    position = Vector2i(100000000, 0);
}

void Spaceship::update(double dt, std::vector<GravData>* gravData, bool focus)
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

    bool burn = false;
    if (focus)
    {
        if (Joystick::getAxisPosition(0, Joystick::X) < -DEADZONE)
        angularMomentum += Joystick::getAxisPosition(0, Joystick::X) / 100.0;
        if (Joystick::getAxisPosition(0, Joystick::X) >  DEADZONE)
            angularMomentum += Joystick::getAxisPosition(0, Joystick::X) / 100.0;
        if (Joystick::isButtonPressed(0, 0))
            angularMomentum = 0;
        if (Joystick::getAxisPosition(0, Joystick::R) > -100 + DEADZONE)
            burn = true;
    }


    Vector2f acceleration;

    rotation += angularMomentum * dt;

    acceleration.x = Fgrav.x / mass;
    acceleration.y = Fgrav.y / mass;

    if (burn)
    {
        float BURNPOWER = (Joystick::getAxisPosition(0, Joystick::R) + 100) / 10;
        acceleration.x += cos(rotation * (pi / 180)) * BURNPOWER;
        acceleration.y += sin(rotation * (pi / 180)) * BURNPOWER;
    }

    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;

    Vector2f newPos;
    newPos.x = position.x + velocity.x;
    newPos.y = position.y + velocity.y;

    bool collision = false;
    for (int i = 0; i < gravData->size(); i++)
    {
        float newDistance = sqrt(pow(newPos.x - gravData->at(i).x, 2) + pow(newPos.y - gravData->at(i).y, 2));
        if (newDistance < gravData->at(i).radius)
        {
            collision = true;
            velocity = gravData->at(i).velocity;
        }
    }
    std::cout << velocity.x << " " << velocity.y << "\n";

    position.x += velocity.x;
    position.y += velocity.y;
}

void Spaceship::draw(DrawData drawData)
{
    RenderWindow* window = drawData.window;
    double zoom = drawData.zoom;
    Vector2i viewPos = drawData.viewPos;

    for (int i = 0; i < gravForces.size(); i++)
    {
        float mod = 1;
        Vertex grav[] =
        {
            Vertex(globalToDrawCoords(viewPos, position, zoom)),
            Vertex(globalToDrawCoords(viewPos, position, zoom) + Vector2f(gravForces.at(i).x / mod, gravForces.at(i).y / mod))
        };
        grav[0].color = Color::Green;
        grav[1].color = Color::Green;
        window->draw(grav, 2, Lines);
    }

    Vertex velo[] =
    {
        Vertex(globalToDrawCoords(viewPos, position, zoom)),
        Vertex(globalToDrawCoords(viewPos, position, zoom) + velocity)
    };
    velo[0].color = Color::Red;
    velo[1].color = Color::Red;
    window->draw(velo, 2, Lines);

    if (Joystick::getAxisPosition(0, Joystick::R) > -100 + DEADZONE)
    {
        Sprite bigburn;
        bigburn.setTexture(textures->at(1));
        bigburn.setOrigin(15, -33);
        bigburn.setPosition(Vector2f(-drawData.windowWidth / 2 + 72, -drawData.windowHeight / 2 + 72));
        bigburn.setRotation(rotation + 90);
        window->draw(bigburn);
    }

    Sprite ship;
    ship.setTexture(textures->at(0));
    ship.setPosition(Vector2f(-drawData.windowWidth / 2 + 72, -drawData.windowHeight / 2 + 72));
    ship.setRotation(rotation + 90);
    ship.setOrigin(32, 64);
    window->draw(ship);

    if (Joystick::getAxisPosition(0, Joystick::X) < -DEADZONE)
    {
        Sprite smallburn;
        smallburn.setTexture(textures->at(2));
        smallburn.setOrigin(-13, 29);
        smallburn.setPosition(Vector2f(-drawData.windowWidth / 2 + 72, -drawData.windowHeight / 2 + 72));
        smallburn.setRotation(rotation + 90);
        window->draw(smallburn);
    }
    if (Joystick::getAxisPosition(0, Joystick::X) >  DEADZONE)
    {
        Sprite smallburn;
        smallburn.setTexture(textures->at(2));
        smallburn.setOrigin(-13, 29);
        smallburn.setPosition(Vector2f(-drawData.windowWidth / 2 + 72, -drawData.windowHeight / 2 + 72));
        smallburn.setRotation(rotation + 90);
        smallburn.setScale(-1, 1);
        window->draw(smallburn);
    }

    RectangleShape shipMonitor;
    shipMonitor.setSize(Vector2f(140, 140));
    shipMonitor.setFillColor(Color(0, 0, 0, 0));
    shipMonitor.setOutlineColor(Color(0, 200, 0));
    shipMonitor.setOutlineThickness(1);
    shipMonitor.setPosition(Vector2f(-drawData.windowWidth / 2 + 4, -drawData.windowHeight / 2 + 4));
    window->draw(shipMonitor);
}












