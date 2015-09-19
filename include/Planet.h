#ifndef PLANET_H
#define PLANET_H


class Planet
{
    public:
        Planet();
        void update();
        void draw();
    protected:
    private:                       // Mars example values
        float mass = 0;            // 641,710,000,000,000,000,000,000 kg
        float aphelion = 0;        // 249,200,000 km
        float perihelion = 0;      // 206,700,000 km
        float radius = 0;          // 3,389 km
        double orbitalSpeed = 0;   // 24.007 km/s
        int x = 0;                 // <-- position relative to the sun
        int y = 0;                 // <--/
};

#endif // PLANET_H
