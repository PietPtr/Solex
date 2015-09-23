#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <SFML/Graphics.hpp>
#include "include.h"

using namespace sf;

class Spaceship
{
    public:
        Spaceship(std::vector<Texture>* textures);
        void update(double dsimTime, std::vector<GravData>* gravData, bool focus);
        void draw(DrawData drawData);
        Vector2i getPosition() { return position; }
        void setPosition(Vector2i val) { position = val;}
    protected:
    private:
        double mass = 12600; // kg
        double rotation = 0; // degrees
        double angularMomentum = 0; // degrees per second
        Vector2i position; // global coordinates (km)
        Vector2f velocity; // meters per second
        std::vector<Texture>* textures;

        std::vector<Vector2f> gravForces;
};

#endif // SPACESHIP_H
