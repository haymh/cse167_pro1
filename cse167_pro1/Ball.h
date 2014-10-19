#ifndef _BALL_H_
#define _BALL_H_

#include "Vector4d.h"
#include "Vector3d.h"
#include "Matrix4d.h"

class Ball{
protected:
	double acceleration;				// how fast the speed increase or decrease
	double x_speed;						// speed along x direction
	double y_speed;						// speed along y direction
	double z_speed;
	double y_deceleration;				// deceleration in y direction
	double x_deceleration;				// deceleration in x direction
	double z_deceleration;				// deceleration in z direction
	Vector4d center;					// center of the ball
	Vector3d center3d;
	Vector3d color;
	double radius;						// radius of the ball
	double sec_per_call;				// second per function call
	double bounce_loss;					// energy loss when bouncing
	Matrix4d translation;				// the matrix tracking ball's movement
	Matrix4d temp;
	bool x_stopped;
	bool y_stopped;
	bool z_stopped;
	char* name;

public:
	Ball();
	Ball(Vector3d c);
	Ball(char* name, double acc, double xs, double ys, double zs, double dec, Vector3d ce, Vector3d co, double ra, double spc, double bl);
	void setColor(Vector3d);
	Vector3d getColor();
	void randomColor();
	void setCenter(Vector3d);
	void randomSpeed(double min, double max);
	bool isReady();
	void reset();
	void xBounce();
	void yBounce();
	void zBounce();
	bool getX_stopped();
	bool getY_stopped();
	bool getZ_stopped();
	bool isBallStopped();
	double getX_speed();
	double getY_speed();
	double getZ_speed();
	void bounceDirection(double x, double y, double z);
	Vector3d& getCenter();
	Vector3d getVelocity();
	double getX();
	double getY();
	double getZ();
	void setRadius(double);
	double getRadius();
	void move();
	Matrix4d getMatrix();
	void translate(double, double, double);
	double getBounceLoss();
	void setVelocity(Vector3d&);

};

#endif