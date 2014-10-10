#ifndef _WINDOW_H_
#define _WINDOW_H_

class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	            // window size
	static double spin_deg;					// cube rotation degree


    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyboardProcess(unsigned char key, int x, int y);
};

#endif

