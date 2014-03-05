#define GL_LOG_FILE "gl.log"
#ifndef _GLLOG_H_
#define _GLLOG_H_
#include <GL/glew.h> 
#define GLFW_DLL 
#include <GL/glfw3.h>
#include <time.h>
#include <fstream>

bool restart_gl_log ();


bool gl_log (const char * message, const char * filename, int line);

bool printShaderInfoLog(GLuint obj);

void printProgramInfoLog(GLuint obj);

#endif