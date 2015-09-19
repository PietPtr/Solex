#ifndef AUDIO_H
#define AUDIO_H
#include <SFML/Audio.hpp>

using namespace sf;

class Audio
{
    public:
        void init(std::string _src)
        {
            src = _src;
            buffer.loadFromFile(src);
            sound.setBuffer(buffer);
        }
        void play()
        {
            sound.play();
        }
        void stop()
        {
            sound.stop();
        }
    protected:
    private:
        SoundBuffer buffer;
        Sound sound;
        std::string src; //filename
};

#endif // AUDIO_H
