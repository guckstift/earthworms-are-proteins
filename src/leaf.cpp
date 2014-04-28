
#include "leaf.h"

Leaf::Leaf (Image *img)
	: Mob (img)
{
	vy = 2;
	vx = 2;
	phase = 0;
}

Leaf::~Leaf ()
{
}

void Leaf::advance ()
{
	if (vy == 0) {
		phase = 2;
		vx = 0;
	}
	
	if (phase==0) {
		if (vx > -2) {
			vx -= 0.1;
		}
		else {
			phase = 1;
		}
	}
	else if (phase==1) {
		if (vx < 2) {
			vx += 0.1;
		}
		else {
			phase = 0;
		}
	}
	Mob::advance ();
}
