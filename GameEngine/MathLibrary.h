#ifndef _MATHLIBRARY_H_
#define _MATHLIBRARY_H_

//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Mathmatics.h
//		@details		Mathmatical functions
//		@author			Derek Potter
//		@date created	11/5/2013
//////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <string>

const long double PI = 3.141592653589793;

const long double DegreesToRadians = PI / 180;

const long double RadiansToDegrees = 180 / PI;

//////////////////////////////////////////////////////////////////////////
//		@Class:		oVector2
//		@Details:	A 2 Dimensional Vector
//////////////////////////////////////////////////////////////////////////
class oVector2
{

public:

	oVector2();
	oVector2(float a_fX, float a_fY);

	void operator+=(oVector2 & rpVec);
	oVector2 operator+(oVector2 & rpVec);
	void operator-=(oVector2 & rpVec);
	oVector2 operator-(oVector2 & rpVec);
	float operator*(oVector2 & rpVec);
	void operator=(oVector2 & rpVec);

	void SetVector(float a_fX, float a_fY);

	

	oVector2 Normalise();
	oVector2 Perpendicular();
	
	float Magnitude();

	float GetAngle(oVector2 & rpVec);

	oVector2 LinearInterpolant(oVector2 & rpVec, float a_fDelta);

	~oVector2();


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
	oVector3(float a_fX, float a_fY, float a_fZ);

	void operator+=(oVector3 & rpVec);
	oVector3 operator+(oVector3 & rpVec);
	float operator*(oVector3 & rpVec);
	void operator-=(oVector3 & rpVec);
	oVector3 operator-(oVector3 & rpVec);
	void operator=(oVector3 & rpVec);

	void SetVector(float a_fX, float a_fY, float a_fZ);

	void ConvertPosition(float a_fScreenWidth, float a_fScreenHeight, float a_fWidth, float a_fHeight);

	void oVector3::TinyValueFix();

	oVector3 oVector3::Normalise();

	float oVector3::Magnitude();

	oVector3 CrossProduct(oVector3 & rpVec);

	oVector3 LinearInterpolant(oVector3 & rpVec, float a_fDelta);

	~oVector3();

	float m_fX;
	float m_fY;
	float m_fZ;

};


//////////////////////////////////////////////////////////////////////////
//		@Class:		oVector4
//		@Details:	A 4 Dimensional Vector
//////////////////////////////////////////////////////////////////////////
class oVector4{
public:
	
	oVector4();
	oVector4(float a_fX, float a_fY, float a_fZ, float a_fW);

	void operator=(oVector4 & rpVec);
	oVector4 operator-(oVector4 & rpVec);
	float operator*(oVector4 & rpVec);

	void SetVector(float a_fX, float a_fY, float a_fZ, float a_fW);

	void TinyValueFix();

	oVector4 Normalise();

	float Magnitude();

	oVector4 CrossProduct(oVector4 & rpVec);

	~oVector4();
	
	float m_fX;
	float m_fY;
	float m_fZ;
	float m_fW;

};


//////////////////////////////////////////////////////////////////////////
//		@Class:		oMatrix3x3
//		@Details:	A 3x3 matrix (uses three oVector3's)
//////////////////////////////////////////////////////////////////////////
class oMatrix3x3
{

public:

	oMatrix3x3();

	void operator=(oMatrix3x3 & rpMat);
	void operator*=(oMatrix3x3 & rpMat);
	oMatrix3x3 operator*(oMatrix3x3 & rpMat);

	void ScaleMatrix(float a_fScale);

	oMatrix3x3 RotateMatrixDegrees(float a_fDegrees);
	oMatrix3x3 RotateMatrixRadians(float a_fRadians);

	oVector3 oMatrix3x3::TransformVector(oVector3 & rpVec);

	~oMatrix3x3();

	oVector3 pRowOne;
	oVector3 pRowTwo;
	oVector3 pRowThree;

};


//////////////////////////////////////////////////////////////////////////
//		@Class:		oMatrix4x4
//		@Details:	A 4x4 matrix (uses Four oVector4's)
//////////////////////////////////////////////////////////////////////////
class oMatrix4x4
{
	//column notation 
	//0 4 8  12
	//1 5 9  13
	//2 6 10 14
	//3 7 11 15

public:

	oMatrix4x4();

	void operator=(oMatrix4x4 & rpMat);
	void operator*=(oMatrix4x4 & rpMat);
	oMatrix4x4 operator*(oMatrix4x4 & rpMat);

	void ScaleMatrix(float a_fScale);

	oMatrix4x4 RotateMatrixDegrees(float a_fDegrees);
	oMatrix4x4 RotateMatrixRadians(float a_fRadians);

	oMatrix4x4 OrthographicProjectionMatrix(float a_fXMin, float a_fXMax, float a_fYMin, float a_fYMax, float a_fZMin, float a_fZMax);

	oVector3 TransformPoint(oVector3 & rpVec);
	oVector3 TransformVector(oVector3 & rpVec);

	~oMatrix4x4();

	oVector4 pRowOne;
	oVector4 pRowTwo;
	oVector4 pRowThree;
	oVector4 pRowFour;

};


//////////////////////////////////////////////////////////////////////////
//		@Class:		oHex
//		@Details:	Hexadecimal color values in both decimal and hexadecimal formats
//////////////////////////////////////////////////////////////////////////
class oHex{

public:

	oHex();

	void operator=(oHex & rpHex);
	void operator=(oVector4 & rpVec);

	void SetHex(std::string a_sRed, std::string a_sGreen, std::string a_sBlue, float a_fAlpha);
	void SetHex(int a_iRed, int a_iGreen, int a_iBlue, float a_fAlpha);

	oVector4 m_pColorValue;

	std::string m_sRed;
	std::string m_sGreen;
	std::string m_sBlue;
	float m_fAlpha;

	oVector4 m_pPercentValue;

	~oHex();

private:

	void StringChecker(std::string & a_rsStr);

	float SingleConverter(std::string & a_rsStr);
	std::string SingleConverter(int a_iIn);

	oVector4 ConvertFromHex();
	void ConvertToHex();

	void ConvertToPercent();

};


#endif