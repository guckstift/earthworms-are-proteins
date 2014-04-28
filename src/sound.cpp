
#include "sound.h"

Sound::Sound (char *filename)
{
	chunk = Mix_LoadWAV (filename);
}

Sound::~Sound ()
{
}

void Sound::play ()
{
	Mix_PlayChannel (-1, chunk, 0);
}

void Sound::loop ()
{
	Mix_PlayChannel (-1, chunk, -1);
}
