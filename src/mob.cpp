
#include "mob.h"

Mob::Mob (Image *img, Camera *cam)
	: Sprite (img, cam)
{
	vx = 0.0;
	vy = 0.0;
}

void Mob::advance ()
{
	x += vx;
	y += vy;
}

