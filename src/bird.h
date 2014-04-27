
#ifndef BIRD_H
#define BIRD_H

#define LBOUND 128
#define RBOUND (1024-128)
#define BOTTOM (GRID_OFFY+18)

#include "mob.h"

class Bird : public Mob
{
public:
	int state; // 0 = idling ; 1 = hopping ; 2 = attack ; 3 = snap
	int framesRemain;
	int destX;
	int destFieldX;
	int dir; // 0=left;1=right
	Image *imgs[3];
	Earthworms *parent;
	
	Bird (Image *imgs[], Earthworms *parent);
	~Bird ();
	
	void action ();
	void enterIdling ();
	void enterHopping ();
	bool possiblyAttack ();
	//void enterAttack (
	void enterSnap ();
};

#endif

