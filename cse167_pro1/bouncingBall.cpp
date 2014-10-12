#include "bouncingBall.h"

BouncingBall::BouncingBall(){
	acceleration = 0.5;
	x_speed = 1.0;
	z_speed = -1.0;
	y_speed = 0.0;
	floor = -5;
	deceleration = 0.05;
	x_deceleration = deceleration / 15;
	z_deceleration = deceleration / 15;
	center = Vector4d(0, 0, 0, 1);
	radius = 3;
	sec_per_call = 0.01;
	down = true;
	ready = false;
	x_stopped = false;
	y_stopped = false;
	z_stopped = false;
}

BouncingBall::BouncingBall(double acc, double xs, double ys, double zs, int fl, double dec, Vector4d ce, double ra, double spc){
	acceleration = acc;
	x_speed = xs;
	y_speed = ys;
	z_speed = zs;
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
	z_stopped = false;
}

void BouncingBall::move(){
	if (x_stopped && y_stopped && z_speed)
		return;
	double dx = 0;
	double dy = 0;
	double dz = 0;
	if (!x_stopped){									// figure out dx and x_speed
		if (x_speed > 0){
			dx = (x_speed - 0.5 * x_deceleration * sec_per_call) * sec_per_call;
			x_speed -= x_deceleration * sec_per_call;
			if (abs(x_speed) < 0.00005)
				x_stopped = true;
		}
		else{
			dx = (x_speed + 0.5 * x_deceleration * sec_per_call) * sec_per_call;
			x_speed += x_deceleration * sec_per_call;
			if (abs(x_speed) < 0.00005)
				x_stopped = true;
		}
	}
	if (!z_stopped){									// figure out dz and z_speed
		if (z_speed > 0){
			dz = (z_speed - 0.5 * z_deceleration * sec_per_call) * sec_per_call;
			z_speed -= z_deceleration * sec_per_call;
			if (abs(z_speed) < 0.00005)
				z_stopped = true;
		}
		else{
			dz = (z_speed + 0.5 * z_deceleration * sec_per_call) * sec_per_call;
			z_speed += z_deceleration * sec_per_call;
			if (abs(z_speed) < 0.00005)
				z_stopped = true;
		}
	}
	if (!y_stopped){									// figure out dy and y_speed
		if (down){
			double a = -acceleration + deceleration;
			dy = (y_speed + 0.5 * a * sec_per_call) * sec_per_call;
			y_speed += a * sec_per_call;
		}
		else{
			double a = -(acceleration + deceleration);
			dy = (y_speed + 0.5 * a * sec_per_call) * sec_per_call;
			y_speed += a * sec_per_call;
		}
	}

	temp.makeTranslate(dx, dy, dz);
	center = temp * center;
	if (!y_stopped){										// check if collision happens
		if (down){
			if (center[1] <= floor){
				y_speed = -y_speed;
				down = false;
			}
		}
		else{
			if (y_speed <= 0){
				down = true;
				if ((center[1] - floor) < 0.1)
					y_stopped = true;
			}
		}
	}

	if (!x_stopped){
		if (center[0] <= -10 || center[0] >= 10)				// check if collision happens
			x_speed = -x_speed;
	}
	if (!z_stopped){
		if (center[2] <= -10 || center[2] >= 10)				// check if collision happens
			z_speed = -z_speed;
	}
	translation.multiply(temp);
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
	z_stopped = false;
	//x_speed = 1.0;
	//z_speed = -1.0;
	//y_speed = 0.0;
}

void BouncingBall::randomSpeed(){
	double min = -1.0;
	double max = 1.0;
	x_speed = min + ((double)rand() / RAND_MAX) * (max - min);
	y_speed = min + ((double)rand() / RAND_MAX) * (max - min);
	z_speed = min + ((double)rand() / RAND_MAX) * (max - min);
}

void BouncingBall::translate(double dx, double dy, double dz){
	temp.makeTranslate(dx, dy, dz);
	center = temp * center;
	translation.multiply(temp);
}

Matrix4d BouncingBall::getMatrix(){
	return translation;
}