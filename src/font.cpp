
#include <iostream>
#include "font.h"
#include "image.h"
#include "display.h"

using namespace std;

Font::Font (char *filename, int ptsize)
{
	font = TTF_OpenFont (filename, ptsize);
	if (font == 0) {
		cerr << "TTF error: " << TTF_GetError () << endl;
		exit (-1);
	}
}

Image *Font::createText (Display *display, char *text, unsigned int fgcol)
{
	Image *res = new Image (display);
	SDL_Color *col = new SDL_Color;
	*col = *(SDL_Color*)&fgcol;
	SDL_Surface *surf = TTF_RenderText_Solid (font, text, *col);
	res->tex = SDL_CreateTextureFromSurface (display->renderer, surf);
	res->fw = res->w = surf->w;
	res->fh = res->h = surf->h;
	SDL_FreeSurface (surf);
	return res;
}
