#pragma once
#include <SDL.h>
#include <SDL_Mixer.h>
#include <string>
class Sound {
public:
	int sos;
	Mix_Chunk* sample[32];
	std::string sample_names[32];

	Sound();
	int add(std::string soundname);
	void play(int number, float volume = 100);
};

extern Sound sound;