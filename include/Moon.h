#ifndef MOON_H
#define MOON_H

//using namespace sf;

class Moon
{
    public:
        Moon();
    protected:
    private:
        double mass = 0;
        int periapsis = 0;
        int apoapsis = 0;
        int radius = 0;
        Vector2i orbitCenter;
        int orbitalPeriod = 0;
        Vector2i position;
        int phase = 0;
};

#endif // MOON_H
