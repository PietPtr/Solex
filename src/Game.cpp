#include <SFML/Graphics.hpp>
#include <dirent.h>
#include <fstream>
#include "Game.h"
#include "include.h"
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
    sun.loadPlanets();
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
            {
                timeSpeed*=2;
                std::cout << timeSpeed << " time speed\n";
            }
            if (event.key.code == Keyboard::Down)
            {
                timeSpeed/=2;
                std::cout << timeSpeed << " time speed\n";
            }
            if (event.key.code == (Keyboard::X))
            {
                zoom *= 2;
                std::cout << zoom << " zoom\n";
            }
            if (event.key.code == (Keyboard::Z))
            {
                zoom /= 2;
                std::cout << zoom << " zoom\n";
            }
            if (event.key.code == Keyboard::R)
            {
                SPEED *= 10;
                std::cout << SPEED << " speed\n";
            }
            if (event.key.code == Keyboard::F)
            {
                SPEED /= 10;
                std::cout << SPEED << "speed\n";
            }
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

    if (focus)
    {
        if (Keyboard::isKeyPressed(Keyboard::W))
            viewPos.y -= SPEED * dt.asSeconds();
        if (Keyboard::isKeyPressed(Keyboard::A))
            viewPos.x -= SPEED * dt.asSeconds();
        if (Keyboard::isKeyPressed(Keyboard::S))
            viewPos.y += SPEED * dt.asSeconds();
        if (Keyboard::isKeyPressed(Keyboard::D))
            viewPos.x += SPEED * dt.asSeconds();
    }


    sun.update(simtime);

    frame++;
}

void Game::draw()
{
    DrawData drawData;
    drawData.window = window;
    drawData.zoom = zoom;
    drawData.viewPos = viewPos;

    if (!Keyboard::isKeyPressed(Keyboard::C))
        window->clear();

    view.setSize(Vector2f(windowWidth, windowHeight));
    view.setCenter(Vector2f(0, 0));
    window->setView(view);

    sun.draw(drawData);

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

void Game::loadAudio(std::vector<std::string> audioFileNames)
{
    for (int i = 0; i < audioFileNames.size(); i++)
    {
        sfx.push_back(new Audio());
        sfx.back()->init(audioFileNames[i]);
    }
}






