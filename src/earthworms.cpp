
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include "earthworms.h"
#include "display.h"
#include "image.h"
#include "worm.h"
#include "cherry.h"

Earthworms::Earthworms ()
	: Game ("Earthworms are Proteins", 1024, 768)
{
	for (int x = 0; x < GRID_COLS; x++) {
		for (int y = 0; y < GRID_ROWS; y++) {
			setObst (x,y,false);
		}
	}
	
	cherry = 0;
	
	srand (time (0));
	
	imgBackground = new Image (display, "res/background.png");
	imgGrid = new Image (display, "res/grid.png");
	imgWorm = new Image (display, "res/worm.png", 4, 4);
	imgCherry = new Image (display, "res/cherry.png");
	
	worm = new Worm (imgWorm, this);
}

Earthworms::~Earthworms ()
{
}

void Earthworms::run ()
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
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					worm->turn (8);
					break;
				case SDLK_RIGHT:
					worm->turn (2);
					break;
				case SDLK_UP:
					worm->turn (1);
					break;
				case SDLK_DOWN:
					worm->turn (4);
					break;
				}
				break;
			}
		}
		// time for another frame?
		int curtick = SDL_GetTicks ();
		if (curtick-lasttick >= FRAMELEN) {
			lasttick = curtick;
			
			//
			// ACTION
			//
			
			if (cherry==0) {
				cherry = new Cherry (
			}
			
			worm->action ();
						
			//
			// DRAWING
			//
			
			display->clear ();
			
			imgBackground->draw ();
			
			int ox = 15, oy = 200;
			for (int x=0; x<GRID_COLS; x++) {
				for (int y=0; y<GRID_ROWS; y++) {
					imgGrid->draw (GRID_OFFX + x*32, GRID_OFFY + y*32, 1, 1, 0, 0, 0.25);
				}
			}
			
			worm->draw ();
			
			display->present ();
		}
	}
}

int main (int argc, char *argv[])
{
	Earthworms *game = new Earthworms ();
	
	game->run ();
	
	delete game;
		
	return 0;
}

void Earthworms::setObst (int x, int y, bool s)
{
	if (x < 0 || x >= GRID_COLS || y < 0 || y >= GRID_ROWS)
		return;
	obstacles [y*GRID_COLS + x] = s;
}

bool Earthworms::getObst (int x, int y)
{
	if (x < 0 || x >= GRID_COLS || y < 0 || y >= GRID_ROWS)
		return true;
	else
		return obstacles [y*GRID_COLS + x];
}

