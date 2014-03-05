#include <GL\glew.h>


#define GLFW_DLL
#include <GL\glfw3.h>


#include <stdio.h>
#include "Objects.h"

oRender pRender;

int main()
{

	pRender.RenderStartUp();

oObject * tester1 = new oObject("Ball.png",10,10,oVector4(1,1,1,1),pRender.window);
tester1->PhysicsSetup(oVector4(7.0f,7.0f,1000.0f,5.0f), oVector3(400, 580, 0), oVector2(1,1), oVector2(0.5f,0.5f), 5.0f);

oObject * tester2 = new oObject("Ball.png",10,10,oVector4(1,1,1,1),pRender.window);
tester2->PhysicsSetup(oVector4(5.0f,5.0f,1000.0f,5.0f), oVector3(450, 580, 0), oVector2(1,1), oVector2(0.5f,0.5f), 1.0f);

	while (!glfwWindowShouldClose (pRender.window)) {

		pRender.RenderLoopStart();

		tester1->UpdatePosition();
		tester1->Draw();
		tester1->m_pPhysics.Input(false);

		tester2->UpdatePosition();
		tester2->Draw();
		tester2->m_pPhysics.Input(false);

		pRender.RenderLoopEnd();


	}

	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;


}