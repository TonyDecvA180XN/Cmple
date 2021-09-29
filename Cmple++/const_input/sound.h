#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <string>
#include <string.h>
#include "audiere\audiere.h"

using namespace audiere;

class Sound {
private:
    static const int number_of_sounds = 10;
    OutputStreamPtr sound[number_of_sounds];

public:
    void Load(std::string path);

    void Play();

    void Stop();

    bool IsPlaying();
};

#endif // SOUND_H_INCLUDED
