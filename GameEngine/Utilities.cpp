#include <Utilities.h>

int g_gl_width = 800;
int g_gl_height = 600;

float g_DeltaTime = 0;
float g_PreviousTime = 0;
float g_TimeFromStart = 0;

oMatrix4x4 * Ortho;

void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, oMatrix4x4 * mat){

	float deltaX = a_fRight - a_fLeft;
	float deltaY = a_fTop - a_fBottom;
	float deltaZ = a_fNear - a_fFar;

	mat->pRowOne.SetVector(2.f / deltaX, 0.f, 0.f, 0.f);
	mat->pRowTwo.SetVector(0.f, 2.f / deltaY, 0.f, 0.f);
	mat->pRowThree.SetVector(0.f, 0.f, 2.f / deltaZ, 0.f);
	mat->pRowFour.SetVector(((a_fLeft + a_fRight) / (a_fLeft - a_fRight)), ((a_fBottom + a_fTop)/(a_fBottom - a_fTop)), (-(a_fNear + a_fFar)/(a_fFar - a_fNear)), 1.f);

}

//call back before initalization of GLFW
void glfw_error_callback (int error, const char* description) {
	fputs (description, stderr);
	gl_log (description, __FILE__, __LINE__);
}