
#ifndef WORM_H
#define WORM_H

#include <list>

using namespace std;

class Image;
class Earthworms;

inline int invDir (int dir);

class Worm
{
public:
	class Segment
	{
	public:
		int x, y;
		int f; // frame
		int p; // pattern
		int d; // dir
		
		Segment (int x, int y, int f, int p, int d);
	};
	Image *img;
	Earthworms *parent;
	int len;
	list<Segment*> segments;
	int speed; // moves per second
	int duration;
	int dir; //  1 = up; 2 = right; 4 = down ; 8 = left
	int nextDir;
	bool dead;
	
	Worm (Image *img, Earthworms *parent);
	~Worm ();
	void draw ();
	void action ();
	void advance ();
	void turn (int dir);
	
	list<Segment*>::iterator getSegment (int n);
};

#endif

