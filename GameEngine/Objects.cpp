#include "Objects.h"

oObject::oObject(){

}

oObject::~oObject(){

}

oObject::oObject(const char* a_pTexture, int a_iWidth, int a_iHeight, oVector4 a_v4Color, GLFWwindow * window){

	m_pPhysics.pSprite = oSprite(a_pTexture, a_iWidth, a_iHeight, a_v4Color, window);


}

void oObject::PhysicsSetup(oVector4 a_v4Acceleration, oVector3 a_v3Position, oVector2 a_v2SurfaceArea, oVector2 a_v2DampingForce, float a_fMass){

	m_pPhysics.m_bOnGround = 0;
	m_pPhysics.m_v2Velocity = oVector2(0,0);

	m_pPhysics.m_v4Acceleration = a_v4Acceleration;
	m_pPhysics.pSprite.m_v3Position = a_v3Position;
	m_pPhysics.m_v2SurfaceArea = a_v2SurfaceArea;
	m_pPhysics.m_v2DampingForce = a_v2DampingForce;
	m_pPhysics.m_fMass = a_fMass;

}

void oObject::Draw(){

	m_pPhysics.pSprite.Draw();

}

void oObject::UpdatePosition(){

	m_pPhysics.pSprite.m_v3Position.m_fX += m_pPhysics.m_v2Velocity.m_fX;
	m_pPhysics.pSprite.m_v3Position.m_fY += m_pPhysics.m_v2Velocity.m_fY;

}