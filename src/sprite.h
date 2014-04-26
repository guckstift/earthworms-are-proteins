
#ifndef sprite_H
#define sprite_H

#include "drawable.h"

class Image;
class Camera;

class Sprite : public Drawable
{
public:
	double x, y;
	double sx, sy; // scaling 0..1
	double cx, cy; // ranged 0..1
	double angle; // 0.0 means looking along negative y-axis, walking clockwise
	double alpha;
	int frame;
	Image *img;
	Camera *cam;

	Sprite (Image *img, Camera *cam = 0);
	void draw ();
	int getScreenX ();
	int getScreenY ();
};

#endif

