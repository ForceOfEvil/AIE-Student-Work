#include "Physics.h"


oPhysics::oPhysics(){
}
	
oPhysics::~oPhysics(){
}

//////////////////////////////////////////////////////////////////////////
//		Runs physics for top down games, or games without gravity
//////////////////////////////////////////////////////////////////////////
void oPhysics::RunTopDown(bool a_bLeft, bool a_bRight, bool a_bUp, bool a_bDown){

	oVector2 v2Friction;

	v2Friction.SetVector(10 * m_v2DampingForce.m_fX * -m_v2Velocity.m_fX * m_v2SurfaceArea.m_fX, 10 * m_v2DampingForce.m_fY * -m_v2Velocity.m_fY * m_v2SurfaceArea.m_fY);

	m_v2Velocity.m_fX += ((((-m_v4Acceleration.m_fX * a_bLeft) + (m_v4Acceleration.m_fY * a_bRight)) + v2Friction.m_fX) / m_fMass) * g_DeltaTime;
	m_v2Velocity.m_fY += ((((m_v4Acceleration.m_fZ * a_bUp) + (-m_v4Acceleration.m_fW * a_bDown)) + v2Friction.m_fY) / m_fMass) * g_DeltaTime;

}

//////////////////////////////////////////////////////////////////////////
//		Runs physics for side-scrolling games
//////////////////////////////////////////////////////////////////////////
void oPhysics::RunSideScroll(bool a_bLeft, bool a_bRight, bool a_bJump){

	oVector2 v2Friction;

	v2Friction.SetVector(10* m_v2DampingForce.m_fX * -m_v2Velocity.m_fX * m_v2SurfaceArea.m_fX, 10* m_v2DampingForce.m_fY * -m_v2Velocity.m_fY * m_v2SurfaceArea.m_fY);

	m_v2Velocity.m_fX += ((((-m_v4Acceleration.m_fX * a_bLeft) + (m_v4Acceleration.m_fY * a_bRight)) + v2Friction.m_fX) / m_fMass) * g_DeltaTime;
	m_v2Velocity.m_fY += ((((m_v4Acceleration.m_fZ * a_bJump * m_fMass) + v2Friction.m_fY) / m_fMass) * g_DeltaTime) + ((1 - m_bOnGround) * cfGravity * m_fMass);

}

//////////////////////////////////////////////////////////////////////////
//		Tests Screen Collision 1-L,2-R,4-U,8-D, 3-LR,5-LU,6-RU,7LRU,9-LD,10-RD,11-LRD,12-UD,13-LUD,14-RUD,15-LRUD
//////////////////////////////////////////////////////////////////////////
int oPhysics::ScreenCollision(){

	int iReturnValue = 0;

	if(pSprite.m_v3Position.m_fX <= (pSprite.m_v2Scale.m_fX/2)){
		iReturnValue += 1;
		m_v2Velocity.m_fX = 0;
	}

	if(pSprite.m_v3Position.m_fX >= (g_gl_width - pSprite.m_v2Scale.m_fX/2)){
		iReturnValue += 2;
		m_v2Velocity.m_fX = 0;
	}

	if(pSprite.m_v3Position.m_fY <= (pSprite.m_v2Scale.m_fY/2)){
		iReturnValue += 4;
		m_v2Velocity.m_fY = 0;
		m_bOnGround = 1;
	}

	if(pSprite.m_v3Position.m_fY >= (g_gl_height - pSprite.m_v2Scale.m_fY/2)){
		iReturnValue += 8;
		m_v2Velocity.m_fY = 0;

	}

	return iReturnValue;

}

//////////////////////////////////////////////////////////////////////////
//		Handles the inputs, and runs the physics via topdown or sidescroll
//////////////////////////////////////////////////////////////////////////
void oPhysics::Input(bool a_bTopDown)
{

	bool bLeft = 0;
	bool bRight = 0; 
	bool bUp = 0; 
	bool bDown = 0;

	int iCollision;

	iCollision = ScreenCollision();
	
	if (GLFW_PRESS == glfwGetKey(pSprite.GameWindow, GLFW_KEY_W) && (m_bOnGround == 1 || a_bTopDown == 1) && (iCollision != 8 && iCollision != 9 && iCollision != 10 && 
			iCollision != 11 && iCollision != 12 && iCollision != 13 && iCollision != 14 && iCollision != 15))
        {
			bUp = 1;
			m_bOnGround = 0;
	  }

        if (GLFW_PRESS == glfwGetKey(pSprite.GameWindow, GLFW_KEY_A) && (m_bOnGround == 1 || a_bTopDown == 1) && (iCollision != 1 && iCollision != 3 && iCollision != 5 && 
			iCollision != 7 && iCollision != 9 && iCollision != 11 && iCollision != 13 && iCollision != 15))
        {
            bLeft = 1;
        }

        if (GLFW_PRESS == glfwGetKey(pSprite.GameWindow, GLFW_KEY_S) && (m_bOnGround == 1 || a_bTopDown == 1) && (iCollision != 4 && iCollision != 5 && iCollision != 6 && 
		  iCollision != 7 && iCollision != 12 && iCollision != 13 && iCollision != 14 && iCollision != 15))
        {
			bDown = 1;
		}

        if (GLFW_PRESS == glfwGetKey(pSprite.GameWindow, GLFW_KEY_D) && (m_bOnGround == 1 || a_bTopDown == 1) && (iCollision != 2 && iCollision != 3 && iCollision != 6 &&
			iCollision != 7 && iCollision != 10 && iCollision != 11 && iCollision != 14 && iCollision != 15))
        {
            bRight = 1;
        }

		if(a_bTopDown == true)
			RunTopDown(bLeft, bRight, bUp, bDown);
		else
			RunSideScroll(bLeft, bRight, bUp);

}