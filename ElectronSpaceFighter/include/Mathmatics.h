//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Mathmatics.h
//		@details		Mathmatical functions
//		@author			Derek Potter
//		@date created	11/5/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

const long double PI = 3.141592653589793;

//////////////////////////////////////////////////////////////////////////
//		@Class:		oVector2
//		@Details:	A 2 Dimensional Vector
//////////////////////////////////////////////////////////////////////////
class oVector2
{

public:

	oVector2();
	float oVector2::GetVectorX();
	float oVector2::GetVectorY();
	void oVector2::SetVector(float a_fX, float a_fY);

//////////////////////////////////////////////////////////////////////////
//		Adds one vector to another
//////////////////////////////////////////////////////////////////////////
	void operator+=(oVector2 & rpVec){
		m_fX += rpVec.m_fX;
		m_fY += rpVec.m_fY;
	};

//////////////////////////////////////////////////////////////////////////
//		Adds two vectors and returns the value
//////////////////////////////////////////////////////////////////////////
	oVector2 operator+(oVector2 & rpVec){
		oVector2 Dummy;
		Dummy.SetVector(m_fX + rpVec.m_fX, m_fY + rpVec.m_fY);
		return Dummy;
	};

//////////////////////////////////////////////////////////////////////////
//		Subtracts one vector to another
//////////////////////////////////////////////////////////////////////////
	void operator-=(oVector2 & rpVec){
		SetVector(m_fX - rpVec.m_fX, m_fY - rpVec.m_fY);
	};

//////////////////////////////////////////////////////////////////////////
//		Subtracts two vectors and returns the value
//////////////////////////////////////////////////////////////////////////
	oVector2 operator-(oVector2 & rpVec){
		oVector2 Dummy;
		Dummy.SetVector(m_fX - rpVec.m_fX, m_fY - rpVec.m_fY);
		return Dummy;
	};

//////////////////////////////////////////////////////////////////////////
//		Makes a vector equal to another
//////////////////////////////////////////////////////////////////////////
	void operator=(oVector2 & rpVec){
		m_fX = rpVec.m_fX;
		m_fY = rpVec.m_fY;
	};

	double oVector2::DotProduct(oVector2 & rpVec);

	oVector2 oVector2::Normalize();
	oVector2 oVector2::Perpendicular(oVector2 &rpVec);
	
	double oVector2::Magnitude();

	double oVector2::ConvertToDegrees(double a_Radians);

	double oVector2::GetAngle(oVector2 & rpVec);

	~oVector2();

private:

	float m_fX;
	float m_fY;

};

//////////////////////////////////////////////////////////////////////////
//		@Class:		oVector3
//		@Details:	A 3 Dimensional Vector
//////////////////////////////////////////////////////////////////////////
class oVector3
{

public:

	oVector3();
	float oVector3::GetVectorX();
	float oVector3::GetVectorY();
	float oVector3::GetVectorZ();
	void oVector3::SetVector(float a_fX, float a_fY, float a_fZ);

	void operator+=(oVector3 & rpVec){
		m_fX += rpVec.m_fX;
		m_fY += rpVec.m_fY;
		m_fZ += rpVec.m_fZ;
	};

	void operator=(oVector3 & rpVec){
		m_fX = rpVec.m_fX;
		m_fY = rpVec.m_fY;
		m_fZ = rpVec.m_fZ;
	};

	double oVector3::DotProduct(oVector3 & rpVec);

	oVector3 oVector3::Normalize();

	double oVector3::Magnitude();

	double oVector3::ConvertToDegrees(double a_Radians);

	oVector3 oVector3::CrossProduct(oVector3 & rpVecB);

	~oVector3();

private:

	float m_fX;
	float m_fY;
	float m_fZ;

};

class oMatrix3x3
{

public:

	oMatrix3x3();

	void oMatrix3x3::SetMatrix(float a_OneOne, float a_OneTwo, float a_OneThree,
							   float a_TwoOne, float a_TwoTwo, float a_TwoThree,
							   float a_ThreeOne, float a_ThreeTwo, float a_ThreeThree){

		m_iMatrix[0][0] = a_OneOne;
		m_iMatrix[0][1] = a_OneTwo;
		m_iMatrix[0][2] = a_OneThree;

		m_iMatrix[1][0] = a_TwoOne;
		m_iMatrix[1][1] = a_TwoTwo;
		m_iMatrix[1][2] = a_TwoThree;

		m_iMatrix[2][0] = a_ThreeOne;
		m_iMatrix[2][1] = a_ThreeTwo;
		m_iMatrix[2][2] = a_ThreeThree;

	}

	void operator*=(oMatrix3x3 & rpMat){

	};

	oMatrix3x3 operator*(oMatrix3x3 & rpMat){
		oMatrix3x3 Dummy;
		Dummy.SetMatrix(m_iMatrix[0][0] * rpMat.m_iMatrix[0][0] + m_iMatrix[1][0] * rpMat.m_iMatrix[0][1] + m_iMatrix[2][0] * rpMat.m_iMatrix[0][2],
						m_iMatrix[0][0] * rpMat.m_iMatrix[1][0] + m_iMatrix[1][0] * rpMat.m_iMatrix[1][1] + m_iMatrix[2][0] * rpMat.m_iMatrix[1][2],
						m_iMatrix[0][0] * rpMat.m_iMatrix[2][0] + m_iMatrix[1][0] * rpMat.m_iMatrix[2][1] + m_iMatrix[2][0] * rpMat.m_iMatrix[2][2],
						m_iMatrix[0][1] * rpMat.m_iMatrix[0][0] + m_iMatrix[1][1] * rpMat.m_iMatrix[0][1] + m_iMatrix[2][1] * rpMat.m_iMatrix[0][2],
						m_iMatrix[0][1] * rpMat.m_iMatrix[1][0] + m_iMatrix[1][1] * rpMat.m_iMatrix[1][1] + m_iMatrix[2][1] * rpMat.m_iMatrix[1][2],
						m_iMatrix[0][1] * rpMat.m_iMatrix[2][0] + m_iMatrix[1][1] * rpMat.m_iMatrix[2][1] + m_iMatrix[2][1] * rpMat.m_iMatrix[2][2],
						m_iMatrix[0][2] * rpMat.m_iMatrix[0][0] + m_iMatrix[1][2] * rpMat.m_iMatrix[0][1] + m_iMatrix[2][2] * rpMat.m_iMatrix[0][2],
						m_iMatrix[0][2] * rpMat.m_iMatrix[1][0] + m_iMatrix[1][2] * rpMat.m_iMatrix[1][1] + m_iMatrix[2][2] * rpMat.m_iMatrix[1][2],
						m_iMatrix[0][2] * rpMat.m_iMatrix[2][0] + m_iMatrix[1][2] * rpMat.m_iMatrix[2][1] + m_iMatrix[2][2] * rpMat.m_iMatrix[2][2]);
						
		return Dummy;
	};

	~oMatrix3x3();


private:

	float m_iMatrix[3][3];

};


#endif