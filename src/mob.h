
#ifndef mob_H
#define mob_H

#include "sprite.h"

class Image;
class Camera;

class Mob : public Sprite
{
public:
	double vx, vy;
	
	Mob (Image *img, Camera *cam = 0);
	void advance ();
};

#endif

