#ifndef _BOUNCINGBALL_H_
#define _BOUNCINGBALL_H_

#include "Vector4d.h"
#include "Matrix4d.h"

class BouncingBall{
protected:
	double acceleration;				// how fast the speed increase or decrease
	double x_speed;						// speed along x direction
	double y_speed;						// speed along y direction
	double z_speed;
	int floor;							// position of the floor
	double deceleration;				// deceleration in y direction
	double x_deceleration;				// deceleration in x direction
	double z_deceleration;				// deceleration in z direction
	Vector4d center;					// center of the ball
	double radius;						// radius of the ball
	bool down;							// true -- the ball is going down, false it is going up
	double sec_per_call;				// second per function call
	Matrix4d translation;				// the matrix tracking ball's movement
	Matrix4d temp;
	bool ready;
	bool x_stopped;
	bool y_stopped;
	bool z_stopped;

public:
	BouncingBall();
	BouncingBall(double acc, double xs, double ys, double zs, int fl, double dec, Vector4d ce, double ra, double spc);
	void randomSpeed();
	bool isReady();
	void reset();
	void drop();
	void move();
	Matrix4d getMatrix();
	void translate(double, double, double);

};

#endif