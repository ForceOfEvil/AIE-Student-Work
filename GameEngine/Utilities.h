#ifndef _UTIL_H_
#define _UTIL_H_
#include <GL\glew.h>
#include <GL\glfw3.h>

#include "MathLibrary.h"
#include "GLLog.h"
#include "TextFileReader.h"


#include <string>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <functional>
#include "MathLibrary.h"

extern int g_gl_width;
extern int g_gl_height;

extern float g_DeltaTime;
extern float g_PreviousTime;
extern float g_TimeFromStart;

struct Vertex
{
	union
	{
		struct 
		{
			oVector3 Pos;
			oVector4 Color;
			oVector2 UV;
		};
		
		struct
		{
			float X, Y, Z, W;
			float R, G, B, A;
			float U, V;
		};
	};
	

	bool operator == (const Vertex& rhs)
	{
		return (X == rhs.X && Y == rhs.Y && Z == rhs.Z && W == rhs.W && U == rhs.U && V == rhs.V && R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A );
	}
};

extern oMatrix4x4 * Ortho;

void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, oMatrix4x4 * mat);

void glfw_window_size_callback (GLFWwindow* window, int width, int height);

void glfw_error_callback (int error, const char* description);

#endif