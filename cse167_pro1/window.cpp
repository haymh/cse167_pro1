#include <iostream>
#include "Window.h"
#include "Cube.h"
#include "Matrix4d.h"
#include "main.h"
#include "GL\glew.h"
#include "GL\glut.h"
#include "Ball.h"
#include "World.h"
#include "Camera.h"
#include "parser.h"
#include <vector>

using namespace std;

enum KEY{ F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12 };

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
int Window::old_x = width / 2;
int Window::old_y = height / 2;
Vector4d Window::centerOfCube = Vector4d(0, 0, 0, 1);
bool Window::isCube = true;
KEY key = F1;					// store which special key was pressed

vector<Ball*> balls;
World w(-3);

Camera cam1(Vector3d(0, 10, 10), Vector3d(0, 0, 0), Vector3d(0, 1, 0));
Camera cam2(Vector3d(-15, 5, 10), Vector3d(-5, 0, 0), Vector3d(0, 1, 0.5));

vector<double> bunnyPos;
vector<double> dragonPos;
bool bunnyLoaded = false;
double bunny_xmin, bunny_xmax, bunny_ymin, bunny_ymax, bunny_zmin, bunny_zmax, dragon_xmin, dragon_xmax, dragon_ymin, dragon_ymax, dragon_zmin, dragon_zmax;
vector<Vector3d> bunnyNor;
vector<Vector3d> dragonNor;
bool dragonLoaded = false;
Vector3d scaleV(1, 1, 1);



// This data structure defines a simple house

int nVerts = 42;    // your vertex array needs to have this many entries

// These are the x,y,z coordinates of the vertices of the triangles
float vertices[] = {
	-4, -4, 4, 4, -4, 4, 4, 4, 4, -4, 4, 4,     // front face
	-4, -4, -4, -4, -4, 4, -4, 4, 4, -4, 4, -4, // left face
	4, -4, -4, -4, -4, -4, -4, 4, -4, 4, 4, -4,  // back face
	4, -4, 4, 4, -4, -4, 4, 4, -4, 4, 4, 4,     // right face
	4, 4, 4, 4, 4, -4, -4, 4, -4, -4, 4, 4,     // top face
	-4, -4, 4, -4, -4, -4, 4, -4, -4, 4, -4, 4, // bottom face

	-20, -4, 20, 20, -4, 20, 20, -4, -20, -20, -4, -20, // grass
	-4, 4, 4, 4, 4, 4, 0, 8, 4,                       // front attic wall
	4, 4, 4, 4, 4, -4, 0, 8, -4, 0, 8, 4,               // left slope
	-4, 4, 4, 0, 8, 4, 0, 8, -4, -4, 4, -4,             // right slope
	4, 4, -4, -4, 4, -4, 0, 8, -4 };                   // rear attic wall

// These are the RGB colors corresponding to the vertices, in the same order
float colors[] = {
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // front is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // left is green
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // back is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // right is green
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // top is blue
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // bottom is blue

	0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, // grass is dark green
	0, 0, 1, 0, 0, 1, 0, 0, 1,                // front attic wall is blue
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,         // left slope is green
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,         // right slope is red
	0, 0, 1, 0, 0, 1, 0, 0, 1, };              // rear attic wall is red

// The index data stores the connectivity of the triangles; 
// index 0 refers to the first triangle defined above
int indices[] = {
	0, 2, 3, 0, 1, 2,      // front face
	4, 6, 7, 4, 5, 6,      // left face
	8, 10, 11, 8, 9, 10,     // back face
	12, 14, 15, 12, 13, 14,   // right face
	16, 18, 19, 16, 17, 18,   // top face
	20, 22, 23, 20, 21, 22,   // bottom face

	24, 26, 27, 24, 25, 26,   // grass
	28, 29, 30,             // front attic wall
	31, 33, 34, 31, 32, 33,   // left slope
	35, 37, 38, 35, 36, 37,   // right slope
	39, 40, 41 };            // rear attic wall

void Window::loadFiles(){
	Parser::parse("bunny.xyz", bunnyPos, bunnyNor, bunny_xmin, bunny_xmax, bunny_ymin, bunny_ymax, bunny_zmin, bunny_zmax);
	bunnyLoaded = true;
	Parser::parse("dragon.xyz", dragonPos, dragonNor, dragon_xmin, dragon_xmax, dragon_ymin, dragon_ymax, dragon_zmin, dragon_zmax);
	dragonLoaded = true;
}

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
  switch (key){
  case F1:
	  if (isCube)
		  drawCube();
	  else
		  drawBall();
	  break;
  case F2:
	  drawHouse(cam1);
	  break;
  case F3:
	  drawHouse(cam2);
	  break;
  case F4:
	  drawPointCloud(bunnyPos, bunnyNor, bunny_xmin, bunny_xmax, bunny_ymin, bunny_ymax, bunny_zmin, bunny_zmax);
	  break;
  case F5:
	  drawPointCloud(dragonPos, dragonNor, dragon_xmin, dragon_xmax, dragon_ymin, dragon_ymax, dragon_zmin, dragon_zmax);
	  break;
  }
  
  
}

void Window::drawCube(){
	glEnable(GL_LIGHTING);
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

void Window::drawHouse(Camera &cam){
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	Matrix4d glmatrix = cam.getMatrix();
	glLoadMatrixd(glmatrix.getPointer());
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 60; i++){
		int index = indices[i] * 3;
		glColor3f(colors[index], colors[index + 1], colors[index + 2]);
		glVertex3f(vertices[index], vertices[index + 1], vertices[index + 2]);
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void Window::drawBall(){
	glEnable(GL_LIGHTING);
	/*
	Matrix4d glmatrix;
	glmatrix = Globals::ball.getMatrix();
	if (Globals::ball.isReady())
		Globals::ball.move();
	*/
	if (balls.empty()){
		glFlush();
		glutSwapBuffers();
		return;
	}
	w.moveBalls();
	w.collisonCheck();
	for (int i = 0; i < balls.size(); i++){
		Ball * b = balls[i];
		Matrix4d glmatrix;
		glmatrix = b->getMatrix();
		glLoadMatrixd(glmatrix.getPointer());
		Vector3d color = b->getColor();
		glColor3f(color[0], color[1], color[2]);
		glutSolidSphere(b -> getRadius(), 100, 100);
	}
	glFlush();
	glutSwapBuffers();
}

void Window::drawPointCloud(vector<double> &position, vector<Vector3d> &normal, double &x_min, double &x_max, double &y_min, double &y_max, double &z_min, double &z_max){
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	Matrix4d glmatrix;
	Matrix4d scaling;
	Matrix4d translation;
	
	double x = x_max - x_min;
	double y = y_max - y_min;
	double z = z_max - z_min;
	double max = x > y ? (x > z ? x : z) : (y > z ? y : z);
	max /= 1.7;
	double r_max = 20 * sin(30 * M_PI / 180);
	double s = r_max / max;
	scaling.makeScale(s, s, s);
	translation.makeTranslate(-(x_min + x_max) / 2, -(y_min + y_max) / 2, -(z_min + z_max) / 2);
	glmatrix = scaling * translation;
	glLoadMatrixd(glmatrix.getPointer());
	glBegin(GL_POINTS);
	for (int i = 0; i < normal.size(); i++)
	{
		glNormal3d(normal[i][0], normal[i][1], normal[i][2]);
		glVertex3d(position[i*3], position[i*3+1], position[i*3+2]);
	}
	glEnd();

	/* testing the method
	double r_max = 20 * sin(30 * M_PI / 180);
	double s = r_max / 3;
	glmatrix.makeScale(s, s, s);
	glLoadMatrixd(glmatrix.getPointer());
	glColor3f(0, 1, 0);
	glutSolidSphere(3, 100, 100);
	*/
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
		scaleV.scale(0.5);
		break;
	case 'S': //scale up
		Globals::cube.scale(control::UP);
		Globals::cube.printPosition(centerOfCube);
		scaleV.scale(2);
		break;
	case 'b': //switch between ball and cube
		isCube = !isCube;
		break;
	case 27:
		exit(0);
	}
}

void Window::processSpecialKeys(int k, int x, int y){
	switch (k){
	case GLUT_KEY_F1:
		key = F1;
		break;
	case GLUT_KEY_F2:
		key = F2;
		break;
	case GLUT_KEY_F3:
		key = F3;
		break;
	case GLUT_KEY_F4:
		key = F4;
		break;
	case GLUT_KEY_F5:
		key = F5;
		break;
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
			//Globals::ball.randomSpeed();
			//Globals::ball.drop();
			for (int i = 0; i < balls.size(); i++){
				balls[i]->randomSpeed(-2.0, 2.0);
				balls[i]->reset();
			}
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
			
			//Globals::ball.reset();
			Ball * b = new Ball();
			b->setCenter(Vector3d(0, 50, 0));
			b->setRadius(3);
			b->randomColor();
			w.addBall(b);
			balls.push_back(b);
		}
	}
}
