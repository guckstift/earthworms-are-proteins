
#ifndef EARTHWORMS_H
#define EARTHWORMS_H

#define GRID_ROWS 17
#define GRID_COLS 31
#define GRID_OFFX 15
#define GRID_OFFY 200

#include "game.h"

class Image;
class Worm;

class Earthworms : public Game
{
public:
	Image *imgBackground;
	Image *imgGrid;
	Image *imgWorm;
	
	Worm *worm;
	
	Earthworms ();
	~Earthworms ();
	void run ();
};

#endif

