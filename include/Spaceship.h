#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Spaceship
{
    public:
        Spaceship();
        void update();
        void draw();
    protected:
    private:

        double rotation;
        double angularMomentum;
        Vector2f position;
        Vector2f momentum;

        std::vector<Vector2f> gravForces;

};

#endif // SPACESHIP_H
