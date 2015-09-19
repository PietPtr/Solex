#ifndef PLANET_H
#define PLANET_H

struct PlanetData
{
    double mass;
    double aphelion;
    double perihelion;
    double radius;
    double orbitalSpeed;
    int x;
    int y;
};

class Planet
{
    public:
        Planet(PlanetData data);
        void setData(PlanetData data);
        void update();
        void draw();
    protected:
    private:                       // Mars example values
        double mass = 0;            // 641,710,000,000,000,000,000,000 kg
        double aphelion = 0;        // 249,200,000 km
        double perihelion = 0;      // 206,700,000 km
        double radius = 0;          // 3,389 km
        double orbitalSpeed = 0;   // 24.007 km/s
        int x = 0;                 // <-- position relative to the sun
        int y = 0;                 // <--/
};

#endif // PLANET_H
