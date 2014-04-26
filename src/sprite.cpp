
#include "sprite.h"
#include "image.h"
#include "camera.h"

Sprite::Sprite (Image *img, Camera *cam)
{
	this->img = img;
	x = y = 0.0;
	sx = sy = 1.0;
	cx = 0.5;
	cy = 0.5;
	angle = 0.0;
	alpha = 1.0;
	frame = 0;
	this->cam = cam;
}

void Sprite::draw ()
{
	img->draw (getScreenX (), getScreenY (), sx, sy, frame, angle, alpha);
}

int Sprite::getScreenX ()
{
	double screenX = x;
	if (cam) {
		screenX -= cam->x;
		screenX += cam->w / 2;
	}
	screenX -= cx * sx * img->fw;
	return floor (screenX);
}

int Sprite::getScreenY ()
{
	double screenY = y;
	if (cam) {
		screenY -= cam->y;
		screenY += cam->h / 2;
	}
	screenY -= cy * sy * img->fh;
	return floor (screenY);
}

