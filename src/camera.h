
#ifndef camera_H
#define camera_H

class Camera
{
public:
	double x, y; // screen midpoint in world space
	int w, h; // screen dimensions

	Camera (int w, int h);
};

#endif

