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


    for (int i = 0; i < planets.size(); i++)
    {
        planets.at(i).draw(window, zoom, viewPos);
    }
}

void Sun::loadPlanets()
{
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

}
