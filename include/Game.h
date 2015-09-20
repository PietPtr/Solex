#include <SFML/Graphics.hpp>
#include <iostream>
#include "Audio.h"
#include "Spaceship.h"
#include "Planet.h"

using namespace sf;

class Game
{
    public:
        Game(RenderWindow* window);
        void initialize();
        void update();
        void draw();
        bool isWindowOpen();

        void loadAudio(std::vector<std::string> fileNames);
        void loadTextures();
        void loadPlanets();

        int randint(int low, int high, int seed);
        int randint(int low, int high);
    protected:
    private:
        RenderWindow* window;
        View view;
        int windowWidth = 1280;
        int windowHeight = 720;

        bool focus = true;

        Time dt;
        Time totalTime;
        double simtime;
        int timeSpeed = 1;
        Clock clock;
        int frame = 0;

        std::vector<std::string> audioFileNames {};
        std::vector<Texture> textures {};
        std::vector<Planet> planets {};

        std::vector<Audio*> sfx;
};
