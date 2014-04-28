
#ifndef LABEL_H
#define LABEL_H

class Display;
class Image;
class Sprite;
class Font;

class Label
{
public:
	Image *img, *imgShd;
	Sprite *spr, *sprShd;
	
	Label (Display *display, Font *font, char *text, int x, int y, unsigned int fgcol,
		float cx=0.5, float cy=0.5);
	~Label ();
	void draw ();
};

#endif

