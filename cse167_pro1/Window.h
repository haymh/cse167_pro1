#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Vector4d.h"

class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	            // window size
	static Vector4d centerOfCube;


    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyboardProcess(unsigned char key, int x, int y);
};

#endif

