#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Vector4d.h"
#include "Camera.h"
#include <vector>

class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	            // window size
	static Vector4d centerOfCube;
	static bool isCube;
	static int old_x, old_y;


    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyboardProcess(unsigned char key, int x, int y);
	static void processSpecialKeys(int k, int x, int y);
	static void drawCube();
	static void drawBall();
	static void drawHouse(Camera&);
	static void drawPointCloud(std::vector<double> &position, std::vector<Vector3d> &normal, double &x_min, double &x_max, double &y_min, double &y_max, double &z_min, double &z_max);
	static void mouseMotionProcess(int, int);
	static void mouseProcess(int, int, int, int);
	static void loadFiles();
};

#endif

