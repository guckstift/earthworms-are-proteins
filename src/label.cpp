
#include "label.h"
#include "display.h"
#include "image.h"
#include "sprite.h"
#include "font.h"

Label::Label (Display *display, Font *font, char *text, int x, int y, unsigned int fgcol,
	float cx, float cy)
{
	img = font->createText (display, text, fgcol);
	imgShd = font->createText (display, text, 0xff000000);
	spr = new Sprite (img);
	sprShd = new Sprite (imgShd);
	sprShd->cx = spr->cx = cx;
	sprShd->cy = spr->cy = cy;
	spr->x = x;
	spr->y = y;
	sprShd->x = spr->x + 2;
	sprShd->y = spr->y + 2;
}

Label::~Label ()
{
	delete spr;
	delete sprShd;
	delete img;
	delete imgShd;
}

void Label::draw ()
{
	sprShd->draw ();
	spr->draw ();
}
