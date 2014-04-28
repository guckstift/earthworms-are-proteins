
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
class Font;
class Label;

class Earthworms : public Game
{
public:
	Mixer *mixer;
	
	Image *imgBackground;
	Image *imgLogo;
	Image *imgGrid;
	Image *imgWorm[2];
	Image *imgCherry;
	Image *imgLeaf;
	Image *imgStone;
	Image *imgBird [3];
	
	Sound *sndTheme;
	Sound *sndOmnomnom;
	Sound *sndRaffraff;
	Sound *sndBss;
	Sound *sndNyamNyam;
	Sound *sndOuch[3];
	Sound *sndBird[2];
	
	Font *font, *fontSmall;
	
	Worm *worm;
	Cherry *cherry;
	Leaf *leaf;
	Bird *bird;
	
	Label *lblScore;
	
	bool quit;
	
	int obstacles [GRID_ROWS * GRID_COLS]; // 0=none, 1=worm, 2=stone, 3=end
	
	int gameState; // 0 = Welcome ; 1 = Playing ; 2 = Dead, try again?
	int deathReason; // 0 = left territory, 1 = bird ,2 = ate stone, 3=bite itself
	int score;
	int scoreInc;
	
	Earthworms ();
	~Earthworms ();
	void initMatch ();
	void run ();
	void welcomeState ();
	void playState ();
	void retryState ();
	void setObst (int x, int y, int s);
	int getObst (int x, int y);
	void drawStones ();
};

#endif

