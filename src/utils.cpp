
#include <cmath>
#include "utils.h"

double modulo (double x, int y)
{
	int ix = floor (x);
	double f = x - ix;
	return (((ix%y)+y)%y) + f;
}

double radtodeg (double r)
{
	return r * 360.0 / (2.0*PI);
}

double degtorad (double d)
{
	return d * (2.0*PI) / 360.0;
}

double sind (double d)
{
	return sin (degtorad (d));
}

double cosd (double d)
{
	return cos (degtorad (d));
}

