#include <SFML/Graphics.hpp>
#include <iostream>
#include "Audio.h"

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

        int randint(int low, int high, int seed);
        int randint(int low, int high);
    protected:
    private:
        RenderWindow* window;

        Time dt;
        Time totalTime;
        Clock clock;
        int frame = 0;

        std::vector<std::string> audioFileNames { "first.wav", "second.wav" };

        std::vector<Audio*> sfx;
};
