
#include <iostream>
#include "earthworms.h"
#include "worm.h"
#include "image.h"

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

Worm::Worm (Image *img, Earthworms *parent)
{
	this->img = img;
	this->parent = parent;
	len = 2;
	speed = 3;
	duration = 0;
	nextDir = dir = 8;
	dead = false;
	
	segments.clear ();
	int x = GRID_COLS / 2;
	int y = GRID_ROWS / 2;
	segments.push_front (new Segment (x-0,y, 13, 8, dir));
	segments.push_front (new Segment (x-1,y, 9,  10, dir));
	segments.push_front (new Segment (x-2,y, 0,  2, dir));
	parent->setObst (x-0,y,true);
	parent->setObst (x-1,y,true);
	parent->setObst (x-2,y,true);
}

Worm::~Worm ()
{
}

void Worm::draw ()
{
	for (list<Segment*>::iterator it = segments.begin (); it != segments.end (); ++it) {
		img->draw (
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
	if (duration >= FPS / speed) {
		advance ();
		duration = 0;
	}
	duration ++;
}

void Worm::advance ()
{
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
	if (parent->getObst (newX, newY)) {
		dead = true;
		cout << "died" << endl;
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
	
	// get current tail seg
	list<Segment*>::iterator tail = getSegment (-1);
	
	parent->setObst ((*tail)->x, (*tail)->y, false);
	
	list<Segment*>::iterator newTail = getSegment (-2);
	
	cout << (*newTail)->d << endl;
	(*newTail)->p = (*newTail)->d;
	
	switch ((*newTail)->p) {
	case 1: (*newTail)->f = 14; break;
	case 2: (*newTail)->f = 12; break;
	case 4: (*newTail)->f = 15; break;
	case 8: (*newTail)->f = 13; break;
	}
	
	segments.pop_back ();
	
	/*
	for (int y = 0; y < GRID_ROWS; y++) {
		for (int x = 0; x < GRID_COLS; x++) {
			cout << (parent->getObst (x,y) ? "1" : "0");
		}
		cout << endl;
	}
	*/
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

