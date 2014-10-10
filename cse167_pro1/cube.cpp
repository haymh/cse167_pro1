#include "Cube.h"
#include "Matrix4d.h"
#include <iostream>

using namespace std;



Cube::Cube()
{
  angle = 0.0;
  translate_amount = 0.1;
  rotation_amount = 0.1;
  scale_up_amount = 1.1;
  scale_down_amount = 0.9;
  orbiting_amount = 1;
  spin_deg = 0.01;
  t = true;
}

Cube::Cube(double ta, double ra, double sua, double sda, double oa, double sd){
	translate_amount = ta;
	rotation_amount = ra;
	scale_up_amount = sua;
	scale_down_amount = sda;
	t = sd > 0;
	orbiting_amount = oa;
	spin_deg = abs(sd);
	
}

Matrix4d& Cube::getMatrix()
{
	model2world = orbiting * translation * spin_matrix * scaling;
	return model2world;
}

void Cube::spin()
{
	if (t)
		angle += spin_deg;
	else
		angle -= spin_deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  spin_matrix.makeRotateY(angle);   // This creates the matrix to rotate the cube
  
}

void Cube::toggle(){
	t = !t;
}

void Cube::translate(control::DIRECTION d){
	switch (d){
	case control::LEFT:
		temp.makeTranslate(-translate_amount, 0, 0);
		translation.multiply(temp);
		break;
	case control::RIGHT:
		temp.makeTranslate(translate_amount, 0, 0);
		translation.multiply(temp);
		break;
	case control::UP:
		temp.makeTranslate(0, translate_amount, 0);
		translation.multiply(temp);
		break;
	case control::DOWN:
		temp.makeTranslate(0, -translate_amount, 0);
		translation.multiply(temp);
		break;
	case control::IN:
		temp.makeTranslate(0, 0, -translate_amount);
		translation.multiply(temp);
		break;
	case control::OUT:
		temp.makeTranslate(0, 0, translate_amount);
		translation.multiply(temp);
		break;
	}
}

// TODO: feature for future
void Cube::rotateX(control::DIRECTION d){
	switch (d){
	case control::CLOCKWISE:
		
		break;
	case control::COUNTER_CLOCKWISE:
		break;
	}
}


// TODO: feature for future
void Cube::rotateY(control::DIRECTION d){
	switch (d){
	case control::CLOCKWISE:
		break;
	case control::COUNTER_CLOCKWISE:
		break;
	}
}


// TODO: feature for future
void Cube::rotateZ(control::DIRECTION d){
	switch (d){
	case control::CLOCKWISE:
		break;
	case control::COUNTER_CLOCKWISE:
		break;
	}
}


void Cube::scale(control::DIRECTION d){
	switch (d){
	case control::UP:
		temp.makeScale(scale_up_amount, scale_up_amount, scale_up_amount);
		scaling.multiply(temp);
		break;
	case control::DOWN:
		temp.makeScale(scale_down_amount, scale_down_amount, scale_down_amount);
		scaling.multiply(temp);
		break;
	}
}

void Cube::reset(){
	translation.identity();
	rotation.identity();
	scaling.identity();
	spin_matrix.identity();
	orbiting.identity();
	angle = 0.0;
	t = spin_deg > 0;
}

void Cube::orbitZ(control::DIRECTION d){
	switch (d){
	case control::CLOCKWISE:
		temp.makeRotateZ(-orbiting_amount);
		orbiting.multiply(temp);
		break;
	case control::COUNTER_CLOCKWISE:
		temp.makeRotateZ(orbiting_amount);
		orbiting.multiply(temp);
		break;
	}
}

void Cube::printPosition(Vector4d & center){
	Vector4d v4 = orbiting * translation * spin_matrix * scaling * center;
	std::cout << "( " << v4[0] << ", " << v4[1] << ", " << v4[2] << ")" << std::endl;
}
