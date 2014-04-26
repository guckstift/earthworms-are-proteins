
#include "earthworms.h"
#include "worm.h"
#include "image.h"

Worm::Segment::Segment (int x, int y, int f, int a)
{
	this->x = x;
	this->y = y;
	this->f = f;
}

Worm::Worm (Image *img)
{
	this->img = img;
	len = 2;
	speed = 1;
	
	segments.clear ();
	int x = GRID_COLS / 2;
	int y = GRID_ROWS / 2;
	segments.push_front (new Segment (x  , y, 0, 0));
	segments.push_front (new Segment (x+1, y, 5, 0));
}

Worm::~Worm ()
{
}

void Worm::draw ()
{
	for (list<Segment*>::iterator it = segments.begin (); it != segments.end (); ++it) {
		img->draw (
			GRID_OFFX + (*it)->x * 32,
			GRID_OFFY + (*it)->y * 32,
			1, 1, (*it)->f, 0, 1.0
		);
	}
}

void Worm::advance ()
{
}
