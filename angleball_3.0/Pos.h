#ifndef __Pos_h
#define __Pos_h

#include <cmath>

struct Pos{
	Pos(){x = 0; y = 0;}
	Pos(double x_, double y_): x(x_), y(y_) {}
	double x;
	double y;
	bool operator == (Pos r)
	{
		if(floor(x) == floor(r.x) && floor(y) == floor(r.y))
			return true;
		else
			return false;
	}
};

#endif