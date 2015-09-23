#include "Sun.h"
#include <iostream>

using namespace sf;

Vector2f globalToDrawCoords(Vector2i viewPos, Vector2i global, double zoom);

Sun::Sun()
{
    //ctor
}

void Sun::update(double simtime, std::vector<GravData>* gravData, double timeSpeed)
{
    gravData->clear();

    GravData sunGravData;
    sunGravData.mass = mass;
    sunGravData.x = 0;
    sunGravData.y = 0;
    sunGravData.radius = radius;
    gravData->push_back(sunGravData);

    for (int i = 0; i < planets.size(); i++)
    {
        planets.at(i).update(simtime, timeSpeed);

        GravData planetGravitationData;
        planetGravitationData.mass = planets.at(i).getMass();
        planetGravitationData.x = planets.at(i).getPosition().x;
        planetGravitationData.y = planets.at(i).getPosition().y;
        planetGravitationData.radius = planets.at(i).getRadius();
        planetGravitationData.velocity = planets.at(i).getVelocity();
        gravData->push_back(planetGravitationData);
    }

    for (int i = 0; i < moons.size(); i++)
    {
        int orbitingPlanet = moons.at(i).getOrbitingPlanet();
        moons.at(i).setOrbitCenter(planets.at(orbitingPlanet).getPosition());
        moons.at(i).update(simtime, timeSpeed);

        GravData moonGravitationData;
        moonGravitationData.mass = moons.at(i).getMass();
        moonGravitationData.x = moons.at(i).getPosition().x;
        moonGravitationData.y = moons.at(i).getPosition().y;
        moonGravitationData.radius = moons.at(i).getRadius();
        moonGravitationData.velocity = moons.at(i).getVelocity();
        gravData->push_back(moonGravitationData);
    }
}

void Sun::draw(DrawData drawData)
{
    RenderWindow* window = drawData.window;
    double zoom = drawData.zoom;
    Vector2i viewPos = drawData.viewPos;


    CircleShape sun;
    int r = radius / zoom;
    r = r < 2 ? 2 : r;
    sun.setRadius(r);
    sun.setPointCount(1024);
    sun.setPosition(globalToDrawCoords(viewPos, Vector2i(0, 0), zoom));
    sun.setOrigin(Vector2f(r, r));
    sun.setFillColor(Color(200, 200, 0));
    window->draw(sun);

    for (int i = 0; i < moons.size(); i++)
    {
        moons.at(i).draw(window, zoom, viewPos);
    }

    for (int i = 0; i < planets.size(); i++)
    {
        planets.at(i).draw(window, zoom, viewPos);
    }


}

void Sun::loadPlanets()
{
    // ---- Planets ----

    PlanetData mercuryData;
    mercuryData.mass = 3.3011e23;
    mercuryData.aphelion = 69816900;
    mercuryData.perihelion = 46001200;
    mercuryData.radius = 2439.7;
    mercuryData.orbitalSpeed = 47362;
    mercuryData.orbitCenter = Vector2i(9540000, 2650000);
    mercuryData.orbitalPeriod = 7118256;
    mercuryData.color = Color(100, 100, 100);
    planets.push_back(Planet(mercuryData));

    PlanetData venusData;
    venusData.mass = 4.8675e24;
    venusData.aphelion = 108939000;
    venusData.perihelion = 107477000;
    venusData.radius = 6051.8;
    venusData.orbitalSpeed = 35020;
    venusData.orbitCenter = Vector2i(0, 1590000);
    venusData.orbitalPeriod = 19397246;
    venusData.color = Color(255, 255, 150);
    planets.push_back(Planet(venusData));

    PlanetData earthData;
    earthData.mass = 5.972e24;
    earthData.aphelion = 151930000;
    earthData.perihelion = 147095000;
    earthData.radius = 6371;
    earthData.orbitalSpeed = 29780;
    earthData.orbitCenter = Vector2i(0, 0);
    earthData.orbitalPeriod = 365.25 * 86400;//15960;
    earthData.color = Color(150, 170, 255);
    planets.push_back(Planet(earthData));

    PlanetData marsData;
    marsData.mass = 6.4171e23;
    marsData.aphelion =   249200000;
    marsData.perihelion = 206700000;
    marsData.radius = 3389;
    marsData.orbitalSpeed = 24077;
    marsData.orbitCenter = Vector2i(-9540000, 19080000);
    marsData.orbitalPeriod = 59318796;//30000;
    marsData.color = Color(255, 200, 100);
    planets.push_back(Planet(marsData));

    // ---- Moons ----

    PlanetData moonData;
    moonData.mass = 7.3477e22;
    moonData.aphelion = 405400;
    moonData.perihelion = 362600;
    moonData.radius = 1737;
    moonData.orbitalPeriod = 2360584;
    moonData.color = Color(160, 160, 160);
    moonData.orbitingPlanetIndex = 2;
    moons.push_back(Planet(moonData));

    PlanetData phobosData;
    phobosData.mass = 1.0659e16;
    phobosData.aphelion = 9517;
    phobosData.perihelion = 9234;
    phobosData.radius = 11;
    phobosData.orbitalPeriod = 27475;
    phobosData.color = Color(160, 130, 130);
    phobosData.orbitingPlanetIndex = 3;
    moons.push_back(Planet(phobosData));

    PlanetData deimosData;
    deimosData.mass = 1.4762e15;
    deimosData.aphelion = 23471;
    deimosData.perihelion = 23455;
    deimosData.radius = 6;
    deimosData.orbitalPeriod = 109123;
    deimosData.color = Color(80, 80, 80);
    deimosData.orbitingPlanetIndex = 3;
    moons.push_back(Planet(deimosData));
}








