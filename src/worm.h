
#ifndef WORM_H
#define WORM_H

#include <list>

using namespace std;

class Image;

class Worm
{
public:
	class Segment
	{
	public:
		int x, y;
		int f;
		int a;
		
		Segment (int x, int y, int f, int a);
	};
	Image *img;
	int len;
	list<Segment*> segments;
	int speed; // moves per second
	
	Worm (Image *img);
	~Worm ();
	void draw ();
	void advance ();
};

#endif

