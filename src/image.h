
#ifndef image_H
#define image_H

#include <SDL2/SDL.h>

class Display;

class Image
{
public:
	Display *display;
	int w, h;
	int cols, rows;
	int fw, fh;
	SDL_Texture *tex;

	Image (Display *display, char *filename = 0, int cols = 1, int rows = 1);
	Image (Display *display, int width, int height);
	~Image ();
	void draw (int x = 0, int y = 0, double sx = 1.0, double sy = 1.0, int frame = 0,
		double angle = 0.0, double alpha = 1.0);
};

#endif

