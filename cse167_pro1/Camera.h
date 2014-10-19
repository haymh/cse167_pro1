#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Matrix4d.h"
#include "Vector3d.h"


class Camera{
protected:
	Vector3d up;			// up-vector
	Vector3d e;				// projection
	Vector3d d;				// look at
	Matrix4d m;

	void computeMatrix();

public:
	Camera(Vector3d e, Vector3d d, Vector3d up);
	Matrix4d getMatrix();


};

#endif