
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include "mixer.h"
#include "font.h"
#include "label.h"
#include "sound.h"
#include "earthworms.h"
#include "display.h"
#include "image.h"
#include "worm.h"
#include "cherry.h"
#include "leaf.h"
#include "bird.h"

using namespace std;

Earthworms::Earthworms ()
	: Game ("Earthworms are Proteins", 1024, 768)
{
	mixer = new Mixer ();
	
	font = new Font ("res/ComicNeue-Regular.ttf", 45);
	fontSmall = new Font ("res/ComicNeue-Regular.ttf", 25);
	
	srand (time (0));
	
	imgBackground = new Image (display, "res/background.png");
	imgLogo = new Image (display, "res/logo.png");
	imgGrid = new Image (display, "res/grid.png");
	imgWorm[0] = new Image (display, "res/worm.png", 4, 4);
	imgWorm[1] = new Image (display, "res/worm2.png", 4, 4);
	imgCherry = new Image (display, "res/cherry.png");
	imgLeaf = new Image (display, "res/leaf2.png");
	imgStone = new Image (display, "res/stone.png");
	imgBird [0] = new Image (display, "res/bird.png");
	imgBird [1] = new Image (display, "res/bird2.png");
	imgBird [2] = new Image (display, "res/bird3.png");
	
	sndTheme = new Sound ("res/theme.ogg");
	sndOmnomnom = new Sound ("res/omnomnom.ogg");
	sndNyamNyam = new Sound ("res/nyamnyam.ogg");
	sndBss = new Sound ("res/bss.ogg");
	sndOuch[0] = new Sound ("res/ouch1.ogg");
	sndOuch[1] = new Sound ("res/ouch2.ogg");
	sndOuch[2] = new Sound ("res/ouch3.ogg");
	sndBird[0] = new Sound ("res/bird1.ogg");
	sndBird[1] = new Sound ("res/bird2.ogg");
	sndRaffraff = new Sound ("res/raffraff.ogg");
	
	gameState = 0;
	deathReason = 0;
	
	sndTheme->loop ();
}

Earthworms::~Earthworms ()
{
}

void Earthworms::initMatch ()
{
	cherry = 0;
	leaf = 0;
	gameState = 0;
	deathReason = 0;
	lblScore = 0;
	score = 0;
	scoreInc = 1;
	
	for (int x = 0; x < GRID_COLS; x++) {
		for (int y = 0; y < GRID_ROWS; y++) {
			setObst (x,y,0);
		}
	}
	
	for (int i=0; i<10; i++) {
		setObst (rand()%GRID_COLS, 1+rand()%(GRID_ROWS-1), 2);
	}
}

void Earthworms::run ()
{
	quit = false;
	welcomeState ();
	if (quit) return;
	while (true) {
		initMatch ();
		playState ();
		if (quit) return;
		retryState ();
		if (quit) return;
	}
}

void Earthworms::welcomeState ()
{
	Label *lblInfo[3];
	lblInfo[0] = new Label (display, fontSmall,
		"Use the arrow or WASD keys to set direction!", 1024/2, 768/2+200, 0xffffffff);
	lblInfo[1] = new Label (display, fontSmall,
		"Use the space bar to go faster!", 1024/2, 768/2+230, 0xffffffff);
	lblInfo[2] = new Label (display, fontSmall,
		"Bang your head against the keyboard to start!", 1024/2, 768/2+280, 0xffffffff);
	
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
				quit = true;
				break;
			case SDL_KEYDOWN:
				running = false;
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
			
			imgBackground->draw ();
			
			//lblWelcome->draw ();
			imgLogo->draw (1024/2 - 256, 240);
			lblInfo[0]->draw ();
			lblInfo[1]->draw ();
			lblInfo[2]->draw ();
			
			display->present ();
		}
	}
}

void Earthworms::playState ()
{
	running = true;
	
	worm = new Worm (imgWorm, this);
	bird = new Bird (imgBird, this);
	
	int lasttick = SDL_GetTicks ();
	
	// main game loop
	while (running) {
		// poll for events
		SDL_Event event;
		while (SDL_PollEvent (&event) == 1) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				quit = true;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					display->resize (event.window.data1, event.window.data2);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
				case SDLK_a:
					worm->sendCommand (8);
					//cout << "left" << endl;
					//worm->turn (8);
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					worm->sendCommand (2);
					//worm->turn (2);
					//cout << "right" << endl;
					break;
				case SDLK_UP:
				case SDLK_w:
					worm->sendCommand (1);
					//worm->turn (1);
					//cout << "up" << endl;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					worm->sendCommand (4);
					//worm->turn (4);
					//cout << "down" << endl;
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
			cout << 1000.0/(curtick-lasttick) << endl;
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
					imgGrid->draw (GRID_OFFX + x*32, GRID_OFFY + y*32, 1, 1, 0, 0, 0.02);
				}
			}
			
			if (cherry)
				cherry->draw ();
			else if (leaf)
				leaf->draw ();
			
			worm->draw ();
			
			bird->draw ();
			
			drawStones ();
			
			if (lblScore) {
				delete lblScore;
				lblScore = 0;
			}
			char txtbuf [64];
			sprintf (txtbuf, "Score: %d", score);
			lblScore = new Label (display, fontSmall, txtbuf, 16, 16, 0xffffffff, 0, 0);
			lblScore->draw ();
			
			display->present ();
			
			//
			// bird yelling
			//
			
			if (rand()%200 < 1) {
				sndBird [rand()%2]->play ();
			}
		}
		
		// dead the worm fail it's mission?
		
		if (worm->dead) {
			gameState = 2;
			running = false;
		}
	}
}

void Earthworms::retryState ()
{
	int remain = FPS;
	
	// RETRY ? state
	running = true;
	
	int lasttick = SDL_GetTicks ();
	
	Label *lblYouDied [3];
	if (deathReason == 0) {
		lblYouDied [0] = new Label (display, fontSmall, "Earthworms tend to leave their territory", 1024/2, 768/2-100,
			0xffffffff);
		lblYouDied [1] = new Label (display, fontSmall, "for no arguable reason! O.o", 1024/2, 768/2-75,
			0xffffffff);
	}
	else if (deathReason == 1) {
		lblYouDied [0] = new Label (display, fontSmall, "Earthworms tend to be eaten by mean birds", 1024/2, 768/2-100,
			0xffffffff);
		lblYouDied [1] = new Label (display, fontSmall, "way to often! O.o", 1024/2, 768/2-75,
			0xffffffff);
	}
	else if (deathReason == 2) {
		lblYouDied [0] = new Label (display, fontSmall, "Earthworms sometimes are hungry for stones.", 1024/2, 768/2-100,
			0xffffffff);
		lblYouDied [1] = new Label (display, fontSmall, "Unfortunately stones are not good for them! O.o", 1024/2, 768/2-75,
			0xffffffff);
	}
	else if (deathReason == 3) {
		lblYouDied [0] = new Label (display, fontSmall, "Earthworms sometimes bite themselves.", 1024/2, 768/2-100,
			0xffffffff);
		lblYouDied [1] = new Label (display, fontSmall, "This makes them die! O.o", 1024/2, 768/2-75,
			0xffffffff);
	}
	
	Label *lblInfo;
	lblInfo = new Label (display, fontSmall,
		"Stroke your keyboard to retry!", 1024/2, 768-30, 0xffffffff);

	Label *lblYourScore[2];
	lblYourScore[0] = new Label (display, fontSmall,
		"Your score:", 1024/2, 768/2, 0xffffffff);
	
	char txtbuf[6];
	sprintf (txtbuf, "%d", score);
	
	lblYourScore[1] = new Label (display, fontSmall,
		txtbuf, 1024/2, 768/2+60, 0xffffffff);
	
	int scalePhase = 0;
	
	// game loop
	while (running) {
		// poll for events
		SDL_Event event;
		while (SDL_PollEvent (&event) == 1) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (remain <= 0)
					running = false;
				break;
			}
		}
		// time for another frame?
		int curtick = SDL_GetTicks ();
		if (curtick-lasttick >= FRAMELEN) {
			lasttick = curtick;
			
			remain --;
						
			//
			// DRAWING
			//
			
			display->clear ();
			
			imgBackground->draw ();
			
			if (cherry)
				cherry->draw ();
			else if (leaf)
				leaf->draw ();
			
			worm->draw ();
			
			bird->draw ();
			
			drawStones ();
			
			lblYouDied[0]->draw ();
			lblYouDied[1]->draw ();
			
			lblYourScore[0]->draw ();
			
			if (scalePhase==0) {
				lblYourScore[1]->spr->sx += 0.1;
				lblYourScore[1]->spr->sy += 0.1;
				lblYourScore[1]->sprShd->sx += 0.1;
				lblYourScore[1]->sprShd->sy += 0.1;
			}
			else if (scalePhase==1) {
				lblYourScore[1]->spr->sx -= 0.1;
				lblYourScore[1]->spr->sy -= 0.1;
				lblYourScore[1]->sprShd->sx -= 0.1;
				lblYourScore[1]->sprShd->sy -= 0.1;
			}
			if (lblYourScore[1]->spr->sx >= 3)
				scalePhase = 1;
			if (lblYourScore[1]->spr->sx <= 1)
				scalePhase = 0;
			lblYourScore[1]->draw ();
			
			if (remain <= 0)
				lblInfo->draw ();
			
			display->present ();
		}
	}
	
	delete worm;
	delete bird;
	if (cherry) {
		delete cherry;
		cherry = 0;
	}
	if (leaf) {
		delete leaf;
		leaf = 0;
	}
}


int main (int argc, char *argv[])
{
	Earthworms *game = new Earthworms ();
	game->run ();
	delete game;

	return 0;
}

void Earthworms::setObst (int x, int y, int s)
{
	if (x < 0 || x >= GRID_COLS || y < 0 || y >= GRID_ROWS)
		return;
	obstacles [y*GRID_COLS + x] = s;
}

int Earthworms::getObst (int x, int y)
{
	if (x < 0 || x >= GRID_COLS || y < 0 || y >= GRID_ROWS)
		return 3;
	else
		return obstacles [y*GRID_COLS + x];
}

void Earthworms::drawStones ()
{
	for (int x = 0; x < GRID_COLS; x++) {
		for (int y = 0; y < GRID_ROWS; y++) {
			if (getObst(x,y)==2) {
				imgStone->draw (GRID_OFFX + x*32, GRID_OFFY + y*32);
			}
		}
	}
}

