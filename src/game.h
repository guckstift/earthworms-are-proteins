
#ifndef GAME_H
#define GAME_H

#define FPS 60.0
#define FRAMELEN (1000.0/FPS)

using namespace std;

class Display;

class Game
{
public:
	bool running;
	Display *display;
	
	Game ();
	~Game ();
	virtual void run () = 0;
};

#endif

