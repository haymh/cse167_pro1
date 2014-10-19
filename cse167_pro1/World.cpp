#include "World.h"
#include <iostream>

World::World(double fl){
	floor = fl;
}

World::World(Ball& b1, Ball& b2, double fl){
	balls.push_back(&b1);
	balls.push_back(&b2);
	floor = fl;
}

void World::addBall(Ball* b){
	balls.push_back(b);
}

void World::moveBalls(){
	for (int i = 0; i < balls.size(); i++){
		Ball * b = balls[i];
		if (!b->isBallStopped())
			b->move();
	}
}

void World::collisonCheck(){

	if (balls.size() >= 2){
		for (int i = 0; i < balls.size(); i++){
			for (int j = i + 1; j < balls.size(); j++){
				Vector3d c1 = balls[i]->getCenter();
				Vector3d c2 = balls[j]->getCenter();
				double dx = c1[0] - c2[0];
				double dy = c1[1] - c2[1];
				double dz = c1[2] - c2[2];
				double d = sqrt(dx * dx + dy * dy + dz * dz);
				if (d <= (balls[i]->getRadius() + balls[j]->getRadius())){
					Vector3d v = c2 - c1;									// Ball 1
					v.normalize();
					Vector3d velocity1 = balls[i]->getVelocity();
					double m1 = velocity1.dot(v);
					v.scale(m1);											// velocity projection on v
					Vector3d u1 = velocity1 - v;


					Vector3d v2 = c1 - c2;									// Ball 2
					v2.normalize();
					Vector3d velocity2 = balls[j]->getVelocity();
					double m2 = velocity2.dot(v2);
					v2.scale(m2);
					Vector3d u2 = velocity2 - v2;

					if (m1 < 0 && m2 < 0)
						std::cout << "m1: " << m1 << ", m2: " << m2 << std::endl;			// do nothing, they are leaving each other
					else {
						Vector3d newV1 = u1 + v2;
						Vector3d newV2 = u2 + v;
						balls[i]->setVelocity(newV1);
						balls[j]->setVelocity(newV2);
					}
				}
			}
		}
		
	}

	for (int i = 0; i < balls.size(); i++){
		Ball* b = balls[i];
		if (b->isBallStopped())
			return;

		if (!b->getY_stopped()){										// check if collision happens
			if (b->getY_speed() < 0){
				if (b->getY() <= floor){
					b->yBounce();
				}
			}
		}

		if (!b->getX_stopped()){										// check if collision happens
			if (b->getX() <= -7)
				if (b->getX_speed() < 0){
				b->xBounce();
				}

			if (b->getX() >= 7){
				if (b->getX_speed() > 0){
					b->xBounce();
				}
			}
		}

		if (!b->getZ_stopped()){										// check if collision happens
			if (b->getZ() <= -17)
				if (b->getZ_speed() < 0){
				b->zBounce();
				}

			if (b->getZ() >= 3){
				if (b->getZ_speed() > 0){
					b->zBounce();
				}
			}
		}
	}
}