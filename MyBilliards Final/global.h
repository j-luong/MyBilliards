#ifndef GLOBAL_H
#define GLOBAL_H

#include <windows.h>		// Header File For Windows

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#include "Balls.h"
#include "Vector3.h"
#include "ColourOGL.h"
#include "GameObjects.h"

//=============== Function prototypes ====================
//WinMain.cpp
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

//OGL.cpp
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
int InitGL(GLvoid);
int DrawGLScene(GLvoid);
GLvoid KillGLWindow(GLvoid);
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag);

#endif //GLOBAL_H