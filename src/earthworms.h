
#ifndef EARTHWORMS_H
#define EARTHWORMS_H

#define GRID_ROWS 18
#define GRID_COLS 31
#define GRID_OFFX 15
#define GRID_OFFY 168

#include "game.h"

class Image;
class Worm;
class Cherry;
class Leaf;
class Bird;
class Mixer;
class Sound;

class Earthworms : public Game
{
public:
	Mixer *mixer;
	
	Image *imgBackground;
	Image *imgGrid;
	Image *imgWorm[2];
	Image *imgCherry;
	Image *imgLeaf;
	Image *imgBird [3];
	
	Sound *sndOmnomnom;
	Sound *sndNyamNyam;
	Sound *sndOuch[3];
	
	Worm *worm;
	Cherry *cherry;
	Leaf *leaf;
	Bird *bird;
	
	bool obstacles [GRID_ROWS * GRID_COLS];
	
	Earthworms ();
	~Earthworms ();
	void run ();
	void setObst (int x, int y, bool s);
	bool getObst (int x, int y);
};

#endif

