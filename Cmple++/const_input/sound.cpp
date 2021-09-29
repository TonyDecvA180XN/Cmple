#include "sound.h"

void Sound::Load(std::string path) {
    AudioDevicePtr device(OpenDevice());
    sound[0] = OpenSound(device, path.c_str(), false);
    for(int i = 1; i < number_of_sounds; i++)
        sound[i] = sound[0];
}

void Sound::Play(){
    for(int i = 0; i < number_of_sounds; i++) {
        if(!sound[i]->isPlaying()) {
            sound[i]->play();
            break;
        }
    }
}

void Sound::Stop(){
    for(int i = 0; i < number_of_sounds; i++) {
        if(sound[i]->isPlaying()) {
            sound[i]->stop();
        }
    }
}

bool Sound::IsPlaying(){
    for(int i = 0; i < number_of_sounds; i++) {
        if(sound[i]->isPlaying()) {
            return true;
        }
    }
    return false;
}
