
#ifndef LEAF_H
#define LEAF_H

#include "mob.h"

class Leaf : public Mob
{
public:
	int phase; // 0 = accel left ; 1 = accel right ; 2 = still
	Leaf (Image *img);
	~Leaf ();
	void advance ();
};

#endif

