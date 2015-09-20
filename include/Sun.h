#ifndef SUN_H
#define SUN_H
#include "Planet.h"
#include "include.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Sun
{
    public:
        Sun();
        void loadPlanets();
        void update(double simtime, std::vector<GravData>* gravData);
        void draw(DrawData drawData);
        std::vector<Planet>* getPlanets() { return &planets; }
    protected:
    private:
        double mass = 1.98855e30;
        double radius = 696342;
        std::vector<Planet> planets {};
};

#endif // SUN_H
