#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4d.h"

class Cube
{
  protected:
    Matrix4d model2world;            // model matrix (transforms model coordinates to world coordinates)
    double angle;                   // rotation angle [degrees]

  public:
    Cube();   // Constructor
    Matrix4d& getMatrix();
    void spin(double);      // spin cube [degrees]
};

#endif

