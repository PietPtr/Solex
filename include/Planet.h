#ifndef PLANET_H
#define PLANET_H
#include <SFML/Graphics.hpp>
#include "include.h"

using namespace sf;

int randint(int low, int high);



class Planet
{
    public:
        Planet(PlanetData data);
        void setData(PlanetData data);
        void update(double simtime);
        void draw(RenderWindow* window, double zoom, Vector2i viewPos);
        Vector2i getPosition() { return Vector2i(x, y); }
    protected:
    private:                       // Mars example values
        double mass = 0;           // 641,710,000,000,000,000,000,000 kg
        int aphelion = 0;          // 249,200,000 km
        int perihelion = 0;        // 206,700,000 km
        double radius = 0;         // 3,389 km
        double orbitalSpeed = 0;   // 24.007 km/s
        Vector2i orbitCenter;
        int orbitalPeriod = 0;     // 59,353,534 seconds
        int x = 0;                 // <-- position relative to the sun
        int y = 0;                 // <--/
        Color color;
        Vector2f velocity;
};

#endif // PLANET_H
