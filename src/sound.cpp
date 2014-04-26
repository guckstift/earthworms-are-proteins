
#include "sound.h"

Sound::Sound (char *filename)
{
	chunk = Mix_LoadWAV (filename);
}

Sound::~Sound ()
{
}

