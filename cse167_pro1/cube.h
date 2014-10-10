#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4d.h"


namespace control{
	enum DIRECTION { LEFT, RIGHT, UP, DOWN, IN, OUT, CLOCKWISE, COUNTER_CLOCKWISE };
};

class Cube
{
  protected:
    Matrix4d model2world;            // model matrix (transforms model coordinates to world coordinates)
	Matrix4d translation;			// matrix store translation
	Matrix4d inv_translation;		// matrix store inverse of translation
	Matrix4d rotation;				// matrix store rotation
	Matrix4d scaling;				// matrix store scaling
	Matrix4d spin_matrix;			// matrix store spin
	Matrix4d temp;					// tempoary matrix
    double angle;                   // rotation angle [degrees]

  public:
    Cube();   // Constructor
    Matrix4d& getMatrix();
    void spin(double);				// spin cube [degrees]
	void translate(control::DIRECTION);		// translate to the direction small amount
	void rotateX(control::DIRECTION);		// rotate about x axis in the direction small amount
	void rotateY(control::DIRECTION);		// rotate about y axis in the direction small amount
	void rotateZ(control::DIRECTION);		// rotate about z axis in the direction small amount
	void scale(control::DIRECTION);			// scale up or down small amount

  private:
	  static double translate_amount;
	  static double rotation_amount;
	  static double scale_up_amount;
	  static double scale_down_amount;
};

#endif

