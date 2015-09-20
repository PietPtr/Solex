#include <SFML/Graphics.hpp>
#include <dirent.h>
#include <fstream>
#include "Game.h"
#include "Planet.h"

using namespace sf;

Game::Game(RenderWindow* _window)
{
    window = _window;
}

void Game::initialize()
{
    loadAudio(audioFileNames);
    loadTextures();
    loadPlanets();
}

void Game::update()
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                window->close();
            }
            if (event.key.code == Keyboard::Up)
                timeSpeed++;
            if (event.key.code == Keyboard::Down)
                timeSpeed--;
        }
        if (event.type == Event::Resized)
        {
            windowWidth = event.size.width;
            windowHeight = event.size.height;
        }
        if (event.type == Event::LostFocus)
            focus = false;
        if (event.type == Event::GainedFocus)
            focus = true;
    }

    dt = clock.restart();
    totalTime += dt;
    simtime += dt.asSeconds() * timeSpeed;

    for (int i = 0; i < planets.size(); i++)
    {
        std::cout << i << ": ";
        planets.at(i).update(simtime);
    }

    frame++;
}

void Game::draw()
{
    //window->clear();

    view.setSize(Vector2f(windowWidth, windowHeight));
    view.setCenter(Vector2f(0, 0));
    window->setView(view);

    for (int i = 0; i < planets.size(); i++)
    {
        planets.at(i).draw(window);
    }

    window->display();
}

bool Game::isWindowOpen()
{
    return window->isOpen();
}

void Game::loadTextures()
{
    DIR *dir;
    struct dirent *ent;
    dir = opendir("textures/");

    std::vector<std::string> textureNames;

    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (std::string(ent->d_name) != "." && std::string(ent->d_name) != "..")
            {
                textureNames.push_back(std::string(ent->d_name));
            }
        }
        closedir(dir);
    }
    else
    {
        window->close();
    }

    std::sort(textureNames.begin(), textureNames.end());

    for (int i = 0; i < textureNames.size(); i++)
    {
        Texture loadedTexture;
        if (!loadedTexture.loadFromFile("textures/" + textureNames[i]))
            window->close();

        std::cout << "Loaded texture " << "textures/" + textureNames[i] << "\n";

        textures.push_back(loadedTexture);
        textures.at(textures.size() - 1).setRepeated(true);
    }
    std::cout << std::endl;
}

void Game::loadPlanets()
{
    /*PlanetData sunData;
    sunData.mass = 1.98855e30;
    sunData.aphelion = 0;
    sunData.perihelion = 0;
    sunData.radius = 696342;
    sunData.orbitalSpeed = 0;
    sunData.orbitCenter = Vector2i(0, 0);
    sunData.orbitalPeriod = 1;
    planets.push_back(Planet(sunData));*/

    PlanetData mercuryData;
    mercuryData.mass = 3.3011e23;
    mercuryData.aphelion = 69816900;
    mercuryData.perihelion = 46001200;
    mercuryData.radius = 2439.7;
    mercuryData.orbitalSpeed = 47362;
    mercuryData.orbitCenter = Vector2i(9540000, 2650000);
    mercuryData.orbitalPeriod = 60;
    planets.push_back(Planet(mercuryData));

    PlanetData venusData;
    venusData.mass = 4.8675e24;
    venusData.aphelion = 108939000;
    venusData.perihelion = 107477000;
    venusData.radius = 6051.8;
    venusData.orbitalSpeed = 35020;
    venusData.orbitCenter = Vector2i(0, 1590000);
    venusData.orbitalPeriod = 164;
    planets.push_back(Planet(venusData));

    PlanetData earthData;
    earthData.mass = 5.972e24;
    earthData.aphelion = 151930000;
    earthData.perihelion = 147095000;
    earthData.radius = 6371;
    earthData.orbitalSpeed = 29780;
    earthData.orbitCenter = Vector2i(0, 0);
    earthData.orbitalPeriod = 266;
    planets.push_back(Planet(earthData));

    PlanetData marsData;
    marsData.mass = 6.4171e23;
    marsData.aphelion =   249200000;
    marsData.perihelion = 206700000;
    marsData.radius = 3389;
    marsData.orbitalSpeed = 24077;
    marsData.orbitCenter = Vector2i(-9540000, 19080000);
    marsData.orbitalPeriod = 500;
    planets.push_back(Planet(marsData));

}

void Game::loadAudio(std::vector<std::string> audioFileNames)
{
    for (int i = 0; i < audioFileNames.size(); i++)
    {
        sfx.push_back(new Audio());
        sfx.back()->init(audioFileNames[i]);
    }
}

/*void Game::loadPlanets()
{
    DIR *dir;
    struct dirent *ent;
    dir = opendir("planets/");

    std::vector<std::string> planetNames;

    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (std::string(ent->d_name) != "." && std::string(ent->d_name) != "..")
            {
                planetNames.push_back(std::string(ent->d_name));
            }
        }
        closedir(dir);
    }
    else
    {
        window->close();
    }

    std::sort(planetNames.begin(), planetNames.end());

    for (int i = 0; i < planetNames.size(); i++)
    {
        std::cout << planetNames.at(i) << "\n";

        std::string filename = "planets/" + planetNames.at(i);
        std::ifstream file(filename);

        std::vector<std::string> rawData;

        while(!file.eof())
        {
            std::string line;
            std::getline(file, line);
            if (line.length() >= 1)
            {
                rawData.push_back(line);
            }
        }

        PlanetData data;
        data.mass = std::stoi(rawData.at(0), nullptr);
        data.aphelion = std::stoi(rawData.at(1), nullptr);
        data.perihelion = std::stoi(rawData.at(2), nullptr);
        data.radius = std::stoi(rawData.at(3), nullptr);
        data.orbitalSpeed = std::stoi(rawData.at(4), nullptr);
        data.x = std::stoi(rawData.at(5), nullptr);
        data.y = std::stoi(rawData.at(6), nullptr);

        planets.push_back(Planet(data));

        file.close();

    }
}*/














