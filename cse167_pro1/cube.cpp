#include "Cube.h"
#include "Matrix4d.h"

using namespace std;

double Cube::translate_amount = 0.1;
double Cube::rotation_amount = 0.01;
double Cube::scale_up_amount = 1.1;
double Cube::scale_down_amount = 0.9;

Cube::Cube()
{
  angle = 0.0;
}

Matrix4d& Cube::getMatrix()
{
  return model2world;
}

void Cube::spin(double deg)   // deg is in degrees
{
  angle += deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  spin_matrix.makeRotateY(angle);   // This creates the matrix to rotate the cube
  model2world = translation * rotation * spin_matrix * scaling;
}

void Cube::translate(control::DIRECTION d){
	switch (d){
	case control::LEFT:
		temp.makeTranslate(-translate_amount, 0, 0);
		translation.multiply(temp);
		temp.makeTranslate(translate_amount, 0, 0);
		inv_translation.multiply(temp);
		break;
	case control::RIGHT:
		temp.makeTranslate(translate_amount, 0, 0);
		translation.multiply(temp);
		temp.makeTranslate(-translate_amount, 0, 0);
		inv_translation.multiply(temp);
		break;
	case control::UP:
		temp.makeTranslate(0, translate_amount, 0);
		translation.multiply(temp);
		temp.makeTranslate(0, -translate_amount, 0);
		inv_translation.multiply(temp);
		break;
	case control::DOWN:
		temp.makeTranslate(0, -translate_amount, 0);
		translation.multiply(temp);
		temp.makeTranslate(0, translate_amount, 0);
		inv_translation.multiply(temp);
		break;
	case control::IN:
		temp.makeTranslate(0, 0, -translate_amount);
		translation.multiply(temp);
		temp.makeTranslate(0, 0, translate_amount);
		inv_translation.multiply(temp);
		break;
	case control::OUT:
		temp.makeTranslate(0, 0, translate_amount);
		translation.multiply(temp);
		temp.makeTranslate(0, 0, -translate_amount);
		inv_translation.multiply(temp);
		break;
	}
	model2world = translation * rotation * spin_matrix * scaling;
}

void Cube::rotateX(control::DIRECTION d){

}

void Cube::rotateY(control::DIRECTION d){

}

void Cube::rotateZ(control::DIRECTION d){

}

void Cube::scale(control::DIRECTION d){

}
