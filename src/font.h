
#ifndef font_H
#define font_H

#include <SDL2/SDL_ttf.h>

class Display;
class Image;

class Font
{
public:
	TTF_Font *font;

	Font (char *filename, int ptsize);
	Image *createText (Display *display, char *text, unsigned int fgcol);
};

#endif

