
#include <SDL2/SDL.h>
#include "sauerkirsche.h"
#include "display.h"

Sauerkirsche::Sauerkirsche ()
{
}

Sauerkirsche::~Sauerkirsche ()
{
}

void Sauerkirsche::run ()
{
	running = true;
	
	int lasttick = SDL_GetTicks ();
	
	// main game loop
	while (running) {
		// poll for events
		SDL_Event event;
		while (SDL_PollEvent (&event) == 1) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					display->resize (event.window.data1, event.window.data2);
				break;
			}
		}
		// time for another frame?
		int curtick = SDL_GetTicks ();
		if (curtick-lasttick >= FRAMELEN) {
			lasttick = curtick;
						
			//
			// DRAWING
			//
			
			display->clear ();
			
			display->present ();
		}
	}
}

int main ()
{
	Sauerkirsche *game = new Sauerkirsche ();
	
	game->run ();
	
	delete game;
		
	return 0;
}

