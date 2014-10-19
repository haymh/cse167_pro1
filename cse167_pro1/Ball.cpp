#include "Ball.h"
#include <iostream>

Ball::Ball(){
	name = "ball";
	acceleration = 0.5;
	x_speed = 0.0;
	z_speed = 0.0;
	y_speed = 0.0;
	y_deceleration = 0.05;
	x_deceleration = y_deceleration / 15;
	z_deceleration = x_deceleration;
	center3d = Vector3d(0, 0, 0);
	setCenter(center3d);
	translation.makeTranslate(center[0], center[1], center[2]);
	radius = 3;
	sec_per_call = 0.01;
	bounce_loss = 0.8;
	x_stopped = false;
	y_stopped = false;
	z_stopped = false;
}

Ball::Ball(Vector3d c){
	center3d = c;
	setCenter(c);
	translation.makeTranslate(center[0], center[1], center[2]);
	name = "ball";
	acceleration = 0.5;
	x_speed = 0.0;
	z_speed = 0.0;
	y_speed = 0.0;
	y_deceleration = 0.05;
	x_deceleration = y_deceleration / 15;
	z_deceleration = x_deceleration;
	radius = 3;
	sec_per_call = 0.01;
	bounce_loss = 0.8;
	x_stopped = false;
	y_stopped = false;
	z_stopped = false;
}

Ball::Ball(char* n, double acc, double xs, double ys, double zs, double dec, Vector3d ce, Vector3d co, double ra, double spc, double bl){
	name = n;
	acceleration = acc;
	x_speed = xs;
	y_speed = ys;
	z_speed = zs;
	y_deceleration = dec;
	x_deceleration = y_deceleration / 15;
	z_deceleration = x_deceleration;
	center3d = ce;
	color = co;
	setCenter(ce);
	translation.makeTranslate(center[0], center[1], center[2]);
	radius = ra;
	sec_per_call = spc;
	bounce_loss = bl;
	x_stopped = false;
	y_stopped = false;
	z_stopped = false;
}

void Ball::move(){
	if (x_stopped && y_stopped && z_stopped)
		return;
	double dx = 0;
	double dy = 0;
	double dz = 0;
	if (!x_stopped){									// figure out dx and x_speed
		if (x_speed > 0){
			dx = (x_speed - 0.5 * x_deceleration * sec_per_call) * sec_per_call;
			x_speed -= x_deceleration * sec_per_call;
		}
		else{
			dx = (x_speed + 0.5 * x_deceleration * sec_per_call) * sec_per_call;
			x_speed += x_deceleration * sec_per_call;
		}
		if (abs(x_speed) < 0.000005)
			x_stopped = true;
	}
	if (!z_stopped){									// figure out dz and z_speed
		if (z_speed > 0){
			dz = (z_speed - 0.5 * z_deceleration * sec_per_call) * sec_per_call;
			z_speed -= z_deceleration * sec_per_call;
		}
		else{
			dz = (z_speed + 0.5 * z_deceleration * sec_per_call) * sec_per_call;
			z_speed += z_deceleration * sec_per_call;
		}
		if (abs(z_speed) < 0.000005)
			z_stopped = true;
	}
	if (!y_stopped){									// figure out dy and y_speed
		if (y_speed < 0){
			double a = -acceleration + y_deceleration;
			dy = (y_speed + 0.5 * a * sec_per_call) * sec_per_call;
			y_speed += a * sec_per_call;
			if (abs(y_speed) < 0.000005)
				y_stopped = true;
		}
		else{
			double a = -(acceleration + y_deceleration);
			dy = (y_speed + 0.5 * a * sec_per_call) * sec_per_call;
			y_speed += a * sec_per_call;
		}
	}

	temp.makeTranslate(dx, dy, dz);
	center = temp * center;
	translation.multiply(temp);

}


void Ball::reset(){
	x_stopped = false;
	y_stopped = false;
	z_stopped = false;
}

void Ball::randomSpeed(double min, double max){
	x_speed = min + ((double)rand() / RAND_MAX) * (max - min);
	y_speed = 2 * min + ((double)rand() / RAND_MAX) * (max - min) * 2;
	z_speed = min + ((double)rand() / RAND_MAX) * (max - min);
	std::cout << name << "'s x speed: " << x_speed << " y speed: " << y_speed << " z speed: " << z_speed << std::endl;
}

void Ball::randomColor(){
	color.set(0, (double)rand() / RAND_MAX);
	color.set(1, (double)rand() / RAND_MAX);
	color.set(2, (double)rand() / RAND_MAX);
}

void Ball::setCenter(Vector3d c){
	center3d = c;
	center.set(0, c[0]);
	center.set(1, c[1]);
	center.set(2, c[2]);
	translation.makeTranslate(center[0], center[1], center[2]);
}

void Ball::translate(double dx, double dy, double dz){
	temp.makeTranslate(dx, dy, dz);
	center = temp * center;
	translation.multiply(temp);
}

Matrix4d Ball::getMatrix(){
	return translation;
}

Vector3d& Ball::getCenter(){
	center3d.set(0, center[0]);
	center3d.set(1, center[1]);
	center3d.set(2, center[2]);
	return center3d;
}

double Ball::getX(){
	return center[0];
}

double Ball::getZ(){
	return center[2];
}

double Ball::getY(){
	return center[1];
}

void Ball::xBounce(){
	x_speed = -x_speed;
	x_speed *= bounce_loss;
}

void Ball::yBounce(){
	y_speed = -y_speed;
	y_speed *= bounce_loss;
}

void Ball::zBounce(){
	z_speed = -z_speed;
	z_speed *= bounce_loss;
}

void Ball::bounceDirection(double x, double y, double z){
	x_speed += x;
	y_speed += y;
	z_speed += z;
}

double Ball::getRadius(){
	return radius;
}

void Ball::setRadius(double r){
	radius = r;
}

Vector3d Ball::getVelocity(){
	return Vector3d(x_speed, y_speed, z_speed);
}

double Ball::getBounceLoss(){
	return bounce_loss;
}

void Ball::setVelocity(Vector3d & v){
	x_speed = v[0];
	y_speed = v[1];
	z_speed = v[2];
	if (x_speed > 0.000005)
		x_stopped = false;
	if (y_speed > 0.000005)
		y_stopped = false;
	if (z_speed > 0.000005)
		y_stopped = false;
}

bool Ball::getX_stopped(){
	return x_stopped;
}

bool Ball::getY_stopped(){
	return y_stopped;
}

bool Ball::getZ_stopped(){
	return z_stopped;
}

double Ball::getX_speed(){
	return x_speed;
}

double Ball::getY_speed(){
	return y_speed;
}

double Ball::getZ_speed(){
	return z_speed;
}

bool Ball::isBallStopped(){
	return x_stopped && y_stopped && z_stopped;
}

void Ball::setColor(Vector3d co){
	color = co;
}

Vector3d Ball::getColor(){
	return color;
}
