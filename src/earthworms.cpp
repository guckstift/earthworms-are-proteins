
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include "mixer.h"
#include "sound.h"
#include "earthworms.h"
#include "display.h"
#include "image.h"
#include "worm.h"
#include "cherry.h"
#include "leaf.h"
#include "bird.h"

Earthworms::Earthworms ()
	: Game ("Earthworms are Proteins", 1024, 768)
{
	mixer = new Mixer ();
	
	for (int x = 0; x < GRID_COLS; x++) {
		for (int y = 0; y < GRID_ROWS; y++) {
			setObst (x,y,false);
		}
	}
	
	cherry = 0;
	leaf = 0;
	
	srand (time (0));
	
	imgBackground = new Image (display, "res/background.png");
	imgGrid = new Image (display, "res/grid.png");
	imgWorm[0] = new Image (display, "res/worm.png", 4, 4);
	imgWorm[1] = new Image (display, "res/worm2.png", 4, 4);
	imgCherry = new Image (display, "res/cherry.png");
	imgLeaf = new Image (display, "res/leaf2.png");
	imgBird [0] = new Image (display, "res/bird.png");
	imgBird [1] = new Image (display, "res/bird2.png");
	imgBird [2] = new Image (display, "res/bird3.png");
	
	sndOmnomnom = new Sound ("res/omnomnom.ogg");
	sndNyamNyam = new Sound ("res/nyamnyam.ogg");
	sndOuch[0] = new Sound ("res/ouch1.ogg");
	sndOuch[1] = new Sound ("res/ouch2.ogg");
	sndOuch[2] = new Sound ("res/ouch3.ogg");
	
	worm = new Worm (imgWorm, this);
	bird = new Bird (imgBird, this);
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
				case SDLK_SPACE:
					worm->turbo = true;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_SPACE:
					worm->turbo = false;
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
			
			if (cherry==0 && leaf==0) {
				if (rand()%2==0) {
					cherry = new Cherry (imgCherry);
					cherry->x = GRID_OFFX + 16 + (rand() % (GRID_COLS*32 - 32));
					cherry->y = 0;
					cherry->vy = 5;
				}
				else {
					leaf = new Leaf (imgLeaf);
					leaf->x = GRID_OFFX + 16 + (rand() % (GRID_COLS*32 - 32));
					leaf->y = 0;
					leaf->vy = 5;
				}
			}
			else {
				if (cherry) {
					cherry->advance ();
					if (cherry->y >= GRID_OFFY) {
						cherry->vy = 0;
					}
				}
				else if (leaf) {
					leaf->advance ();
					if (leaf->y >= GRID_OFFY) {
						leaf->vy = 0;
					}
				}
			}
			
			worm->action ();
			bird->action ();
			
			bird->advance ();
						
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
			
			if (cherry)
				cherry->draw ();
			else if (leaf)
				leaf->draw ();
			
			worm->draw ();
			
			bird->draw ();
			
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

