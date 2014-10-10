#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4d.h"
#include "Vector4d.h"


namespace control{
	enum DIRECTION { LEFT, RIGHT, UP, DOWN, IN, OUT, CLOCKWISE, COUNTER_CLOCKWISE };
};

class Cube
{
  protected:
    Matrix4d model2world;            // model matrix (transforms model coordinates to world coordinates)
	Matrix4d translation;			// matrix store translation
	Matrix4d rotation;				// matrix store rotation
	Matrix4d scaling;				// matrix store scaling
	Matrix4d spin_matrix;			// matrix store spin
	Matrix4d temp;					// tempoary matrix
	Matrix4d orbiting;				// matrix store orbiting
    double angle;                   // rotation angle [degrees]
	double translate_amount;
	double rotation_amount;
	double scale_up_amount;
	double scale_down_amount;
	double orbiting_amount;
	double spin_deg;				// amount of degree of spinning
	bool t;							// direction of spinning
	

  public:
    Cube();   // Constructor
	Cube(double ta, double ra, double sua, double sda, double oa, double sd);
    Matrix4d& getMatrix();
    void spin();							// spin cube [degrees]
	void toggle();							// reverse the direction of spinning
	void translate(control::DIRECTION);		// translate to the direction small amount
	void rotateX(control::DIRECTION);		// rotate about x axis in the direction small amount
	void rotateY(control::DIRECTION);		// rotate about y axis in the direction small amount
	void rotateZ(control::DIRECTION);		// rotate about z axis in the direction small amount
	void orbitZ(control::DIRECTION);		// orbit about window's z axis in the direction small amount
	void scale(control::DIRECTION);			// scale up or down small amount
	void reset();							// reset all settings
	void printPosition(Vector4d & center);	// print out the position of the object according to its original center of the object				

};

#endif

