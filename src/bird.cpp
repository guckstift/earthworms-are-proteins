
#include <cstdlib>
#include <iostream>
#include "game.h"
#include "sound.h"
#include "earthworms.h"
#include "bird.h"
#include "worm.h"

using namespace std;

Bird::Bird (Image *imgs[], Earthworms *parent)
	: parent (parent) , Mob (imgs[0])
{
	x = 200;
	y = BOTTOM;
	cy = 1.0;
	for (int i=0; i<3; i++)
		this->imgs[i] = imgs[i];

	enterIdling ();
}

Bird::~Bird ()
{
}

void Bird::action ()
{
	switch (state) {
	
	// Idle state
	
	case 0:
		if (y >= BOTTOM)
			vy = 0;
		else
			vy ++;
		if (rand()%100 <= 10)
			img = (rand()%2) ? imgs[0] : imgs[1];
		framesRemain --;
		
		// state transition
		if (!possiblyAttack ()) {
			if (framesRemain == 0) {
				if (rand ()%2 == 0) {
					enterIdling ();
				}
				else {
					enterHopping ();
				}
			}
		}
		
		break;
	
	// hopping around state
	
	case 1:
		if (y >= BOTTOM) {
			vy = -6;
			parent->sndBss->play ();
		}
		else
			vy ++;
		if (rand()%100 <= 10)
			img = (rand()%2) ? imgs[0] : imgs[1];
		if (x <= LBOUND) {
			x = LBOUND;
			vx = 0;
			framesRemain = 1;
		}
		else if (x > RBOUND) {
			x = RBOUND;
			vx = 0;
			framesRemain = 1;
		}
		framesRemain --;
		
		// state transition
		if (!possiblyAttack ()) {
			if (framesRemain == 0) {
				if (rand ()%2 == 0) {
					enterIdling ();
				}
				else {
					enterHopping ();
				}
			}
		}
		
		break;
	
	// attack mode
	
	case 2:
		if (y >= BOTTOM) {
			vy = -6;
			parent->sndBss->play ();
		}
		else
			vy ++;
		if (rand()%100 <= 10)
			img = (rand()%2) ? imgs[0] : imgs[1];
		
		// state transition
		
		if ( x >= destX-5 && x <= destX+5) {
			if (parent->getObst (destFieldX, 0)==1) {
				enterSnap ();
			}
			else {
				enterIdling ();
			}
		}
		
		break;
	
	// snatch the worm
	
	case 3:
		if (y >= BOTTOM)
			vy = 0;
		else
			vy ++;
		framesRemain --;
		
		// state transition

		if (framesRemain == 0) {
			if (rand ()%2 == 0) {
				enterIdling ();
			}
			else {
				enterHopping ();
			}
		}
		
		
		break;
	}
}

void Bird::enterIdling ()
{
	state = 0;
	framesRemain = rand () % ((int)FPS*5) + ((int)FPS*1);
	dir = rand()%2;
	if (dir)
		hflip = false;
	else
		hflip = true;
	vx = 0;
	cout << "bird: enter idling " << framesRemain/FPS << endl;
}

void Bird::enterHopping ()
{
	state = 1;
	framesRemain = rand () % ((int)FPS*10) + ((int)FPS*1);
	dir = rand()%2;
	if (dir) {
		vx = - rand()%10;
		hflip = false;
	}
	else {
		vx = + rand()%10;
		hflip = true;
	}
	cout << "bird: enter hopping " << framesRemain/FPS << endl;
}

bool Bird::possiblyAttack ()
{
	int startFieldX;
	
	// shall I attack, is there a yummy worm for me?
	if (parent->worm->dead)
		return false;
	
	destFieldX = -1;
	if (dir) { // left looking
		startFieldX = (x-GRID_OFFX-90) / 32;
		for (int i=startFieldX; i>=0; i--) {
			if (parent->getObst (i, 0)==1) {
				destFieldX = i;
				destX = destFieldX*32 + 16 + GRID_OFFX + 90;
				vx = -6;
				break;
			}
		}
	}
	else { // right looking
		startFieldX = (x-GRID_OFFX+90) / 32;
		for (int i=startFieldX; i<GRID_COLS; i++) {
			if (parent->getObst (i, 0)==1) {
				destFieldX = i;
				destX = destFieldX*32 + 16 + GRID_OFFX - 90;
				vx = +6;
				break;
			}
		}
	}
	if (destFieldX != -1) {
		state = 2;		
		cout << "bird: enter attacking destField " << destFieldX << " destX " << destX;
		cout << " startFieldX " << startFieldX << " vx " << vx << endl;
		
		if (startFieldX == destFieldX) {
			if (parent->getObst (destFieldX, 0)==1) {
				enterSnap ();
			}
		}
		return true;
	}
	else
		return false;
}

void Bird::enterSnap ()
{
	state = 3;
	vx = 0;
	framesRemain = FPS;
	parent->sndRaffraff->play ();
	img = imgs[2];
	cout << "bird: snap " << endl;
	Worm::Segment *wormsHead = *parent->worm->getSegment (0);
	Worm::Segment *wormsSecond = *parent->worm->getSegment (1);
	cout << "  " << wormsHead->x << " " << destFieldX << endl;
	if ((wormsHead->y == 0 && wormsHead->x == destFieldX) ||
		(wormsSecond->y == 0 && wormsSecond->x == destFieldX) )
	{
		parent->worm->die ();
		parent->deathReason = 1;
	}
	else {
		parent->worm->cutAt (destFieldX);
	}
}

