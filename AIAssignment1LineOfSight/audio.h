#pragma once

#include <SDL_mixer.h>
#include <string>
#include <iostream>

/**
@brief Creates an Audio object to handle the SDL_Mixer.
DISCLAIMER - This code is from my PGG SDL Assignment.
*/
class Audio
{
private:
	Mix_Music * audio;
	Mix_Chunk * sound;
public:
	/**
	Constructs an Audio object
	@param std::string The file to be loaded
	@param bool Is it a music file? If false its a sound file
	*/
	Audio(std::string, bool);

	/**
	Destructs a Audio object
	*/
	~Audio();

	/**
	Starts the Audio playing
	Starts the Audio playing, also checks if not playing and starts again
	*/
	void startAudio();

	/**
	Plays the sound effect
	*/
	void playEffect();

	/**
	Stops the Audio playing
	*/
	void stopAudio();
};