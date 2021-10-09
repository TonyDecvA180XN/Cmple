#include "sound.h"

void Sound::Load(std::string path) {
    try {
        AudioDevicePtr device(OpenDevice());
        if (!device)
            throw "Could not initialize audio device";
        sound[0] = OpenSound(device, path.c_str(), false);
        if (!sound[0])
            throw "Could not initialize sound";
        for (int i = 1; i < number_of_sounds; i++)
            sound[i] = sound[0];
        loaded = true;
    }
    catch (char const* err) {
        std::cerr << err << std::endl;
    }
}

void Sound::Play() {
    if (!loaded) {
        std::cerr << "Sound was not successfully initialized" << std::endl;
        return;
    }

    for (int i = 0; i < number_of_sounds; i++) {
        if (!sound[i]->isPlaying()) {
            sound[i]->play();
            break;
        }
    }
}

void Sound::Stop() {
    if (!loaded) {
        std::cerr << "Sound was not successfully initialized" << std::endl;
        return;
    }

    for (int i = 0; i < number_of_sounds; i++) {
        if (sound[i]->isPlaying()) {
            sound[i]->stop();
        }
    }
}

bool Sound::IsPlaying() {
    if (!loaded) {
        std::cerr << "Sound was not successfully initialized" << std::endl;
        return false;
    }

    for (int i = 0; i < number_of_sounds; i++) {
        if (sound[i]->isPlaying()) {
            return true;
        }
    }
    return false;
}
