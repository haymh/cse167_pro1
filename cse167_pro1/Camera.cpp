#include "Camera.h"

Camera::Camera(Vector3d projection, Vector3d lookat, Vector3d upVector){
	e = projection;
	d = lookat;
	up = upVector;
	computeMatrix();
}

Matrix4d Camera::getMatrix(){
	return m;
}

void Camera::computeMatrix(){
	
	Vector3d z = e - d;
	z.normalize();
	Vector3d x = up.cross(z);
	x.normalize();
	Vector3d y = z.cross(x);
	y.normalize();
	m.identity();
	m.set(0, 0, x[0]);
	m.set(1, 0, x[1]);
	m.set(2, 0, x[2]);

	m.set(0, 1, y[0]);
	m.set(1, 1, y[1]);
	m.set(2, 1, y[2]);

	m.set(0, 2, z[0]);
	m.set(1, 2, z[1]);
	m.set(2, 2, z[2]);

	m.set(3, 0, -e[0]);
	m.set(3, 1, -e[1]);
	m.set(3, 2, -e[2]);
}