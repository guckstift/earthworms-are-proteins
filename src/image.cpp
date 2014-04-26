
#include <SDL2/SDL_image.h>
#include "image.h"
#include "display.h"

Image::Image (Display *display, char *filename, int cols, int rows)
{
	this->display = display;
	this->cols = cols;
	this->rows = rows;
	if (filename) {
		tex = IMG_LoadTexture (display->renderer, filename);
		SDL_SetTextureBlendMode (tex, SDL_BLENDMODE_BLEND);
		SDL_QueryTexture (tex, 0, 0, &w, &h);
	}
	else {
		tex = 0;
		w = h = 0;
	}
	fw = w / cols;
	fh = h / rows;
}

Image::Image (Display *display, int width, int height)
{
	this->display = display;
	cols = 1;
	rows = 1;
	fw = w = width;
	fh = h = height;
	tex = SDL_CreateTexture (display->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		w, h);
	SDL_SetTextureBlendMode (tex, SDL_BLENDMODE_BLEND);
}

Image::~Image ()
{
	SDL_DestroyTexture (tex);
}

void Image::draw (int x, int y, double sx, double sy, int frame, double angle,
	double alpha)
{
	int framex = frame % cols;
	int framey = frame / cols;
	SDL_Rect srcrect = {fw * framex, fh * framey, fw, fh};
	SDL_Rect dstrect = {x, y, fw * sx, fh * sy};
	SDL_SetTextureAlphaMod (tex, alpha * 255);
	SDL_RenderCopyEx (display->renderer, tex, &srcrect, &dstrect, angle, 0,
		SDL_FLIP_NONE);
}
