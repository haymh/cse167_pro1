#include <iostream>
#include "Window.h"
#include "Cube.h"
#include "Matrix4d.h"
#include "main.h"
#include "GL\glew.h"
#include "GL\glut.h"


using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
int Window::old_x = width / 2;
int Window::old_y = height / 2;
Vector4d Window::centerOfCube = Vector4d(0, 0, 0, 1);
bool Window::isCube = true;

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
  Globals::cube.spin();   // rotate cube; if it spins too fast try smaller values and vice versa
  displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
  if (isCube)
	  drawCube();
  else
	  drawBall();
  
}

void Window::drawCube(){
	// Tell OpenGL what ModelView matrix to use:
	Matrix4d glmatrix;
	glmatrix = Globals::cube.getMatrix();
	//glmatrix.transpose(); // changed the matrix4d to column major, so dont need to call transpose
	glLoadMatrixd(glmatrix.getPointer());

	// Draw all six faces of the cube:
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue. 
	// To change the color of the other faces you will need to repeat this call before each face is drawn.
	// Draw front face:
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);

	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(-5.0, 5.0, -5.0);

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void Window::drawBall(){
	Matrix4d glmatrix;
	glmatrix = Globals::ball.getMatrix();
	if (Globals::ball.isReady())
		Globals::ball.move();
	glLoadMatrixd(glmatrix.getPointer());
	glColor3f(0.0, 1.0, 0.0);
	glutSolidSphere(3, 100, 100);
	glFlush();
	glutSwapBuffers();
}

void Window::keyboardProcess(unsigned char key, int x, int y){
	switch (key){
	case 't': //switch spin direction between counterclockwise and clockwise
		Globals::cube.toggle();
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'x': //move left
		Globals::cube.translate(control::LEFT);
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'X': //move right
		Globals::cube.translate(control::RIGHT);
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'y': //move down
		Globals::cube.translate(control::DOWN);
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'Y': //move up
		Globals::cube.translate(control::UP);
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'z': //move in
		Globals::cube.translate(control::IN);
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'Z': //move out
		Globals::cube.translate(control::OUT);
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'r': //reset
		Globals::cube.reset();
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'o': //orbit about window z axis counterclockwise
		Globals::cube.orbitZ(control::COUNTER_CLOCKWISE);
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'O': //orbit about window z axis clockwise
		Globals::cube.orbitZ(control::CLOCKWISE);
		Globals::cube.printPosition(centerOfCube);
		break;
	case 's': //scale down
		Globals::cube.scale(control::DOWN);
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'S': //scale up
		Globals::cube.scale(control::UP);
		Globals::cube.printPosition(centerOfCube);
		break;
	case 'b': //switch between ball and cube
		isCube = !isCube;
		break;
	case 27:
		exit(0);
	}
}

void Window::mouseMotionProcess(int x, int y){
	double dx = x - old_x;
	double dy = old_y - y;
	old_x = x;
	old_y = y;
	if (!isCube && !Globals::ball.isReady()){
		Globals::ball.translate(dx / width * 20, dy / height * 20, 0);
	}
}

void Window::mouseProcess(int button, int state, int x, int y){
	if (!isCube){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
			Globals::ball.randomSpeed();
			Globals::ball.drop();
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
			
			Globals::ball.reset();
		}
	}
}
