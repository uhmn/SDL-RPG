#include "Sound.h"
#include "Globals.h"
#include <iostream>

Sound::Sound()
{
	sos = 6;
    Mix_AllocateChannels(4);
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
}

int Sound::add(std::string soundname)
{
    int i = 0;
    for (std::string st : sample_names) {
        if (st == soundname) {
            return i;
        }
        else if (st == "") {
            break;
        }
        i++;
    }
    sample[i] = Mix_LoadWAV((app.datapath + soundname).c_str());
    if (sample[i] == NULL)
    {
        fprintf(stderr, "Unable to load wave file: %s\n", soundname);
    }
    else {
        sample_names[i] = soundname;
    }
    return i;
}

void Sound::play(int number, float volume) 
{
    Mix_VolumeChunk(sample[number], (volume/100)*128);
    Mix_PlayChannel(-1, sample[number], 0);
}

Sound sound;