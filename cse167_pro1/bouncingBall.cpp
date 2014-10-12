#include "bouncingBall.h"

BouncingBall::BouncingBall(){
	acceleration = 0.5;
	x_speed = 1.0;
	y_speed = 0.0;
	floor = -5;
	deceleration = 0.05;
	x_deceleration = deceleration / 10;
	center = Vector4d(0, 0, 0, 1);
	radius = 3;
	sec_per_call = 0.01;
	down = true;
	ready = false;
	x_stopped = false;
	y_stopped = false;
}

BouncingBall::BouncingBall(double acc, double xs, double ys, int fl, double dec, Vector4d ce, double ra, double spc){
	acceleration = acc;
	x_speed = xs;
	y_speed = ys;
	floor = fl;
	deceleration = dec;
	x_deceleration = deceleration / 2;
	center = ce;
	radius = ra;
	sec_per_call = spc;
	down = true;
	ready = false;
	x_stopped = false;
	y_stopped = false;
}

void BouncingBall::move(){
	if (x_stopped && y_stopped)
		return;
	double dx, dy;
	if (x_speed > 0){
		dx = (x_speed - 0.5 * x_deceleration * sec_per_call) * sec_per_call;
		x_speed -= x_deceleration * sec_per_call;
		if (abs(x_speed) < 0.005)
			x_stopped = true;
	}
	else{
		dx = (x_speed + 0.5 * x_deceleration * sec_per_call) * sec_per_call;
		x_speed += x_deceleration * sec_per_call;
		if (abs(x_speed) < 0.005)
			x_stopped = true;
	}
	if (down){
		double a = -acceleration + deceleration;
		dy = (y_speed + 0.5 * a * sec_per_call) * sec_per_call;
		y_speed += a * sec_per_call;
		temp.makeTranslate(dx, dy, 0);
		center = temp * center;
		if (center[1] <= floor){
			y_speed = -y_speed;
			down = false;
		}
		if (center[0] <= -10 || center[0] >= 10)
			x_speed = -x_speed;
		translation.multiply(temp);
	}
	else{
		double a = -(acceleration + deceleration);
		dy = (y_speed + 0.5 * a * sec_per_call) * sec_per_call;
		y_speed += a * sec_per_call;
		temp.makeTranslate(dx, dy, 0);
		center = temp * center;
		if (y_speed <= 0){
			down = true;
			if ((center[1] - floor) < 0.1)
				y_stopped = true;
		}
		if (center[0] <= -10 || center[0] >= 10)
			x_speed = -x_speed;
		translation.multiply(temp);
	}
}

bool BouncingBall::isReady(){
	return ready;
}

void BouncingBall::drop(){
	ready = true;
}

void BouncingBall::reset(){
	ready = false;
	x_stopped = false;
	y_stopped = false;
	x_speed = 1.0;
	y_speed = 0.0;
}

void BouncingBall::translate(double dx, double dy, double dz){
	temp.makeTranslate(dx, dy, dz);
	center = temp * center;
	translation.multiply(temp);
}

Matrix4d BouncingBall::getMatrix(){
	return translation;
}