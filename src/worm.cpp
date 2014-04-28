
#include <iostream>
#include <algorithm>
#include <cmath>
#include <algorithm>
#include "earthworms.h"
#include "sound.h"
#include "worm.h"
#include "image.h"
#include "cherry.h"
#include "leaf.h"

using namespace std;

inline int invDir (int dir)
{
	switch (dir) {
	case 1: return 4;
	case 2: return 8;
	case 4: return 1;
	case 8: return 2;
	}
}

Worm::Segment::Segment (int x, int y, int f, int p, int d)
{
	this->x = x;
	this->y = y;
	this->f = f;
	this->p = p;
	this->d = d;
}

Worm::Worm (Image *imgs[2], Earthworms *parent)
{
	for (int i=0; i<3; i++)
		this->imgs[i] = imgs[i];
	this->parent = parent;
	len = 2;
	speed = 4;
	duration = 0;
	nextDir = dir = 8;
	dead = false;
	haveEaten = false;
	turbo = false;
	
	segments.clear ();
	cutSegs.clear ();
	
	int x = GRID_COLS / 2;
	int y = GRID_ROWS / 2;
	segments.push_front (new Segment (x-0,y, 13, 8, dir));
	segments.push_front (new Segment (x-1,y, 9,  10, dir));
	segments.push_front (new Segment (x-2,y, 0,  2, dir));
	parent->setObst (x-0,y,true);
	parent->setObst (x-1,y,true);
	parent->setObst (x-2,y,true);
	
	commands.clear ();
}

Worm::~Worm ()
{
}

void Worm::draw ()
{
	for (list<Segment*>::iterator it = segments.begin (); it != segments.end (); ++it) {
		imgs[dead ? 1 : 0]->draw (
			GRID_OFFX + (*it)->x * 32,
			GRID_OFFY + (*it)->y * 32,
			1, 1, (*it)->f, 0, 1.0
		);
	}
}

void Worm::action ()
{
	if (dead)
		return;
	if (duration >= FPS / (speed+(turbo?speed:0))) {
		advance ();
		duration = 0;
	}
	duration ++;
}

/*
	really advance by one field
*/

void Worm::advance ()
{
	// set scoreInc
	parent->scoreInc = max(1, (int)(segments.size ()-3));
	
	// execute one turn command
	if (!commands.empty()) {
		int cmd = *commands.begin ();
		turn (cmd);
		commands.pop_front ();
	}
	
	// do the turn
	dir = nextDir;

	// get current head seg
	list<Segment*>::iterator head = getSegment (0);
	
	// coords of old and new head seg
	int oldX = (*head)->x;
	int oldY = (*head)->y;
	int newX = oldX;
	int newY = oldY;
	
	// calculate new head seg coords
	switch (dir) {
	case 1: newY--; break;
	case 2: newX++; break;
	case 4: newY++; break;
	case 8: newX--; break;
	}
	
	// crash?
	if (parent->getObst (newX, newY)==1) {
		die ();
		parent->deathReason = 3;
		return;
	}
	else if (parent->getObst (newX, newY)==2) {
		die ();
		parent->deathReason = 2;
		return;
	}
	else if (parent->getObst (newX, newY)==3) {
		die ();
		parent->deathReason = 0;
		return;
	}

	
	// update old head pattern
	(*head)->p |= dir;
	
	// find the frame the old head
	switch ((*head)->p) {
	case 5: (*head)->f =  8; break;
	case 10: (*head)->f =  9; break;
	case 3: (*head)->f =  6; break;
	case 6: (*head)->f =  4; break;
	case 12: (*head)->f =  5; break;
	case 9: (*head)->f =  7; break;
	}
	
	int newHeadFrame, newHeadPattern;
	switch (dir) {
	case 1: newHeadFrame = 3; newHeadPattern = 4; break;
	case 2: newHeadFrame = 1; newHeadPattern = 8; break;
	case 4: newHeadFrame = 2; newHeadPattern = 1; break;
	case 8: newHeadFrame = 0; newHeadPattern = 2; break;
	}
	
	segments.push_front (new Segment (newX, newY, newHeadFrame, newHeadPattern, nextDir));
	parent->setObst (newX, newY, true);
	
	if (haveEaten) {
		haveEaten = false;
	}
	else {
		// get current tail seg
		list<Segment*>::iterator tail = getSegment (-1);
		
		parent->setObst ((*tail)->x, (*tail)->y, false);
		
		list<Segment*>::iterator newTail = getSegment (-2);
		
		(*newTail)->p = (*newTail)->d;
		
		switch ((*newTail)->p) {
		case 1: (*newTail)->f = 14; break;
		case 2: (*newTail)->f = 12; break;
		case 4: (*newTail)->f = 15; break;
		case 8: (*newTail)->f = 13; break;
		}
		
		segments.pop_back ();
	}
	
	// did worm eat something
	if (parent->cherry && newY==0 && floor ((parent->cherry->x-GRID_OFFX)/32)==newX &&
		parent->cherry->vy == 0 )
	{
		eat ();
		delete parent->cherry;
		parent->cherry = 0;
	}
	if (parent->leaf && newY==0 && floor ((parent->leaf->x-GRID_OFFX)/32)==newX &&
		parent->leaf->vy == 0 )
	{
		eat ();
		delete parent->leaf;
		parent->leaf = 0;
	}
}

void Worm::turn (int dir)
{
	Segment *head = *getSegment (0);
	switch (this->dir) {
	case 1:	if (dir == 4) return; break;
	case 2:	if (dir == 8) return; break;
	case 4:	if (dir == 1) return; break;
	case 8:	if (dir == 2) return; break;
	}
	this->nextDir = dir;
	(*getSegment (0))->d = this->nextDir;
}

list<Worm::Segment*>::iterator Worm::getSegment (int n)
{
	if ( n>=0 ) {
		list<Segment*>::iterator elm = segments.begin ();
		std::advance (elm, n);
		return elm;
	}
	else {
		list<Segment*>::iterator elm = segments.begin ();
		std::advance (elm, segments.size()+n);
		return elm;
	}
}

void Worm::eat ()
{
	haveEaten = true;
	speed += 0.25;
	parent->sndNyamNyam->play ();
	parent->score += parent->scoreInc;
}

void Worm::die ()
{
	if (!dead) {
		dead = true;
		cout << "died" << endl;
		parent->sndOuch [rand()%3]->play ();
	}
}

void Worm::sendCommand (int dir)
{
	//cout << "send " << dir << endl;
	if (find (commands.begin(), commands.end(), dir) == commands.end()) {
		//cout << "push " << dir << endl;
		commands.push_back (dir);
	}
}

void Worm::cutAt (int x)
{
	cout << "cut " << x << endl;
	
	list<Segment*>::iterator it = segments.begin ();
	while ( !((*it)->y == 0 && (*it)->x == x) )  ++ it;
	
	--it;
	(*it)->p = (*it)->d;
	switch ((*it)->p) {
	case 1: (*it)->f = 14; break;
	case 2: (*it)->f = 12; break;
	case 4: (*it)->f = 15; break;
	case 8: (*it)->f = 13; break;
	}
	++it;
	
	while (it != segments.end ()) {
		Segment *curSeg = *it;
		parent->setObst (curSeg->x, curSeg->y, 0);
		segments.erase (it++);
		parent->score --;
		if (parent->score < 0)
			parent->score = 0;
	}
}

