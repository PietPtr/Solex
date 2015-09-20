#include <SFML/Graphics.hpp>
#include <iostream>
#include "Audio.h"
#include "Spaceship.h"
#include "Planet.h"
#include "Sun.h"

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

        int randint(int low, int high, int seed);
        int randint(int low, int high);
    protected:
    private:
        RenderWindow* window;
        View view;
        Vector2i viewPos { 0, 0 };
        int windowWidth = 1280;
        int windowHeight = 720;
        double zoom = 57e4; //kilometers per pixel | km/px

        bool focus = true;

        Time dt;
        Time totalTime;
        double simtime;
        double timeSpeed = 10;
        Clock clock;
        int frame = 0;

        std::vector<std::string> audioFileNames {};
        std::vector<Texture> textures {};

        Sun sun;

        std::vector<Audio*> sfx;
};
