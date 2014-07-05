#ifndef __collision_h
#define __collision_h

class Collision{
public:
	Collision(double xVel, double yVel);
	double GetVelocity();
private:
	double xVel;
	double yVel;
};

#endif