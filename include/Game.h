#include <SFML/Graphics.hpp>
#include <iostream>
#include "Audio.h"
#include "Spaceship.h"
#include "Planet.h"
#include "Sun.h"
#include "include.h"

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
        Vector2i viewPos { 0, 25000000 };
        int windowWidth = 1280;
        int windowHeight = 720;
        double zoom = pow(2, 5); //kilometers per pixel | km/px

        bool focus = true;

        Time dt;
        Time totalTime;
        double simtime = 0;
        double timeSpeed = 16;
        Clock clock;
        int frame = 0;

        std::vector<std::string> audioFileNames {};
        std::vector<Texture> textures {};

        Sun sun;
        std::vector<GravData> gravData;


        std::vector<Audio*> sfx;

        Spaceship player { &textures };

        //debug

        float SPEED = 10e7;
};
