#ifndef _WORLD_H_
#define _WORLD_H_

#include "Ball.h"
#include <vector>

using namespace std;

class World{
protected:
	double floor;
	vector<Ball*> balls;

public:
	World(Ball&, Ball&, double fl);
	World(double fl);
	void addBall(Ball*);
	void collisonCheck();
	void moveBalls();
};

#endif