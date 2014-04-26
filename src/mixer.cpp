
#include "mixer.h"

Mixer::Mixer ()
{
	Mix_Init (MIX_INIT_OGG);
	Mix_OpenAudio (44100, AUDIO_S16SYS, 2, 1024);
}

Mixer::~Mixer ()
{
	Mix_CloseAudio ();
	Mix_Quit ();
}

