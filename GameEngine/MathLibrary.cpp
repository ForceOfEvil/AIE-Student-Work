//////////////////////////////////////////////////////////////////////////
//		@file				Mathmatics.cpp
//		@details			Math implementation
//		@author				Derek Potter
//		@date last edited	11/5/2013
//////////////////////////////////////////////////////////////////////////
#include"MathLibrary.h"

//////////////////////////////////////////////////////////////////////////
//		The constructor
//////////////////////////////////////////////////////////////////////////
oVector2::oVector2(){

	m_fX = 0;
	m_fY = 0;

}

oVector2::oVector2(float a_fX, float a_fY){

	m_fX = a_fX;
	m_fY = a_fY;

}

//////////////////////////////////////////////////////////////////////////
//		Adds one vector to another
//////////////////////////////////////////////////////////////////////////
void oVector2::operator+=(oVector2 & rpVec){
	*this = *this + rpVec;
};

//////////////////////////////////////////////////////////////////////////
//		Adds two vectors and returns the value
//////////////////////////////////////////////////////////////////////////
oVector2 oVector2::operator+(oVector2 & rpVec){
	oVector2 Dummy;
	Dummy.SetVector(m_fX + rpVec.m_fX, m_fY + rpVec.m_fY);
	return Dummy;
};

//////////////////////////////////////////////////////////////////////////
//		Subtracts one vector to another
//////////////////////////////////////////////////////////////////////////
void oVector2::operator-=(oVector2 & rpVec){
	*this = *this - rpVec;
};

//////////////////////////////////////////////////////////////////////////
//		Subtracts two vectors and returns the value
//////////////////////////////////////////////////////////////////////////
oVector2 oVector2::operator-(oVector2 & rpVec){
	oVector2 Dummy;
	Dummy.SetVector(m_fX - rpVec.m_fX, m_fY - rpVec.m_fY);
	return Dummy;
};

//////////////////////////////////////////////////////////////////////////
//		Returns the dot product
//////////////////////////////////////////////////////////////////////////
float oVector2::operator*(oVector2 & rpVec){
	return (m_fX * rpVec.m_fX + m_fY * rpVec.m_fY);
};

//////////////////////////////////////////////////////////////////////////
//		Makes a vector equal to another
//////////////////////////////////////////////////////////////////////////
void oVector2::operator=(oVector2 & rpVec){
	m_fX = rpVec.m_fX;
	m_fY = rpVec.m_fY;
};

//////////////////////////////////////////////////////////////////////////
//		Sets the X and Y vectors
//////////////////////////////////////////////////////////////////////////
void oVector2::SetVector(float a_fX, float a_fY){

	m_fX = a_fX;
	m_fY = a_fY;

}

//////////////////////////////////////////////////////////////////////////
//		Normalizes the vector
//////////////////////////////////////////////////////////////////////////
oVector2 oVector2::Normalise(){

	oVector2 pDummy;

	float fMag = Magnitude();

	pDummy.SetVector(m_fX / fMag, m_fY / fMag);

	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		Gets a vector perpendicular to the current vector
//////////////////////////////////////////////////////////////////////////
oVector2 oVector2::Perpendicular(){

	oVector2 pDummy;

	pDummy.SetVector(m_fY, m_fX * -1);

	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		Gets the magnitude of the vector
//////////////////////////////////////////////////////////////////////////
float oVector2::Magnitude(){

	return sqrt(pow(m_fX, 2) + pow(m_fY, 2));

}

//////////////////////////////////////////////////////////////////////////
//		Gets the angle (in degrees) between two vectors
//////////////////////////////////////////////////////////////////////////
float oVector2::GetAngle(oVector2 & rpVec){

	float Degrees = 0;

	oVector2 Dummy;

	// two vectors mutiplied returns the dot product
	Degrees = *this * rpVec;

	Degrees /= Magnitude() * rpVec.Magnitude();

	Degrees = acos(Degrees);

	//dividing the vecotor by a double returns the double converted into degrees
	Degrees = Degrees * RadiansToDegrees;

	return Degrees;


}

//////////////////////////////////////////////////////////////////////////
//		returns the linear interpolation between two vectors at Delta Time D
//////////////////////////////////////////////////////////////////////////
oVector2 oVector2::LinearInterpolant(oVector2 & rpVec, float a_fDelta){

	oVector2 pDummy;
	pDummy = rpVec - *this;
	pDummy.SetVector(pDummy.m_fX * a_fDelta, pDummy.m_fY * a_fDelta);
	
	return pDummy + *this;
}

//////////////////////////////////////////////////////////////////////////
//		The destructor
//////////////////////////////////////////////////////////////////////////
oVector2::~oVector2(){

	//Gru

}


//////////////////////////////////////////////////////////////////////////
//		The constructor
//////////////////////////////////////////////////////////////////////////
oVector3::oVector3(){

	m_fX = 0;
	m_fY = 0;
	m_fZ = 0;

}

oVector3::oVector3(float a_fX, float a_fY, float a_fZ){

	m_fX = a_fX;
	m_fY = a_fY;
	m_fZ = a_fZ;

}

//////////////////////////////////////////////////////////////////////////
//		Adds one vector to another
//////////////////////////////////////////////////////////////////////////
	void oVector3::operator+=(oVector3 & rpVec){
		*this = *this + rpVec;
	};

//////////////////////////////////////////////////////////////////////////
//		Adds two vectors and returns the value
//////////////////////////////////////////////////////////////////////////
	oVector3 oVector3::operator+(oVector3 & rpVec){
		oVector3 pDummy;
		pDummy.SetVector(m_fX + rpVec.m_fX,m_fY + rpVec.m_fY, m_fZ + rpVec.m_fZ);
		return pDummy;
	};

//////////////////////////////////////////////////////////////////////////
//		returns the dot product of the two vectors
//////////////////////////////////////////////////////////////////////////
	float oVector3::operator*(oVector3 & rpVec){
		return (m_fX * rpVec.m_fX + m_fY * rpVec.m_fY + m_fZ * rpVec.m_fZ);
	};

//////////////////////////////////////////////////////////////////////////
//		Subtracts one vector to another
//////////////////////////////////////////////////////////////////////////
	void oVector3::operator-=(oVector3 & rpVec){
		*this = *this - rpVec;
	};

//////////////////////////////////////////////////////////////////////////
//		Subtracts two vectors and returns the value
//////////////////////////////////////////////////////////////////////////
	oVector3 oVector3::operator-(oVector3 & rpVec){
		oVector3 pDummy;
		pDummy.SetVector(m_fX - rpVec.m_fX,m_fY - rpVec.m_fY, m_fZ - rpVec.m_fZ);
		return pDummy;
	};

//////////////////////////////////////////////////////////////////////////
//		Makes one vector equal to another
//////////////////////////////////////////////////////////////////////////
	void oVector3::operator=(oVector3 & rpVec){
		m_fX = rpVec.m_fX;
		m_fY = rpVec.m_fY;
		m_fZ = rpVec.m_fZ;
	};

//////////////////////////////////////////////////////////////////////////
//		Sets the X, Y and Z vectors
//////////////////////////////////////////////////////////////////////////
void oVector3::SetVector(float a_fX, float a_fY, float a_fZ){

	m_fX = a_fX;
	m_fY = a_fY;
	m_fZ = a_fZ;

}

//////////////////////////////////////////////////////////////////////////
//		Sets the X, and Y vectors to Positions on the screen
//////////////////////////////////////////////////////////////////////////
void oVector3::ConvertPosition(float a_fScreenWidth, float a_fScreenHeight, float a_fWidth, float a_fHeight){

	m_fX = a_fWidth - (1.0005 - a_fWidth / a_fScreenWidth) + ((m_fX) * (.00000274 * a_fScreenWidth));

	m_fY = a_fHeight - (1.0005 - ((2 / a_fScreenHeight) * (a_fHeight / 2)));

}

//////////////////////////////////////////////////////////////////////////
//		Fixes the computers aproximation problems
//////////////////////////////////////////////////////////////////////////
void oVector3::TinyValueFix(){

	if(m_fX < .001 && m_fX > -.001)
		m_fX = 0;

	if(m_fY < .001 && m_fY > -.001)
		m_fY = 0;

	if(m_fZ < .001 && m_fZ > -.001)
		m_fZ = 0;

}

//////////////////////////////////////////////////////////////////////////
//		Returns a normal of the vector
//////////////////////////////////////////////////////////////////////////
oVector3 oVector3::Normalise(){

	oVector3 pDummy;

	float fMag = Magnitude();

	pDummy.SetVector(m_fX / fMag, m_fY / fMag, m_fZ / fMag);

	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		Returns the magnitude
//////////////////////////////////////////////////////////////////////////
float oVector3::Magnitude(){
	
	return sqrt(pow(m_fX, 2) + pow(m_fY, 2) + pow(m_fZ, 2));

}

//////////////////////////////////////////////////////////////////////////
//		Returns the cross product
//////////////////////////////////////////////////////////////////////////
oVector3 oVector3::CrossProduct(oVector3 & rpVec){

	oVector3 pDummy;

	pDummy.SetVector(m_fY * rpVec.m_fZ - m_fZ * rpVec.m_fY,
					 m_fZ * rpVec.m_fX - m_fX * rpVec.m_fZ,
					 m_fX * rpVec.m_fY - m_fY * rpVec.m_fX);

	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		returns the linear interpolation between two vectors a point X
//////////////////////////////////////////////////////////////////////////
oVector3 oVector3::LinearInterpolant(oVector3 & rpVec, float a_fDelta){
	oVector3 pDummy;
	pDummy =  rpVec - *this;
	pDummy.SetVector(pDummy.m_fX * a_fDelta, pDummy.m_fY * a_fDelta, pDummy.m_fZ * a_fDelta);
	
	return pDummy + *this;
}

//////////////////////////////////////////////////////////////////////////
//		The destructor
//////////////////////////////////////////////////////////////////////////
oVector3::~oVector3(){

	//Gru

}


//////////////////////////////////////////////////////////////////////////
//		Constructor
//////////////////////////////////////////////////////////////////////////
oVector4::oVector4(){

	m_fX = 0;
	m_fY = 0;
	m_fZ = 0;
	m_fW = 0;

}

oVector4::oVector4(float a_fX, float a_fY, float a_fZ, float a_fT){

	m_fX = a_fX;
	m_fY = a_fY;
	m_fZ = a_fZ;
	m_fW = a_fT;

}

//////////////////////////////////////////////////////////////////////////
//		Makes one vector equal to another
//////////////////////////////////////////////////////////////////////////
void oVector4::operator=(oVector4 & rpVec){
		m_fX = rpVec.m_fX;
		m_fY = rpVec.m_fY;
		m_fZ = rpVec.m_fZ;
		m_fW = rpVec.m_fW;
	};

//////////////////////////////////////////////////////////////////////////
//		Subtracts two vector4's and returns the results
//////////////////////////////////////////////////////////////////////////
oVector4 oVector4::operator-(oVector4 & rpVec){
	
	oVector4 pDummy;
	pDummy.SetVector(m_fX - rpVec.m_fX, m_fY - rpVec.m_fY, m_fZ - rpVec.m_fZ, m_fW - rpVec.m_fW);
	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		returns the dot product of two vectors
//////////////////////////////////////////////////////////////////////////
float oVector4::operator*(oVector4 & rpVec){
	return (m_fX * rpVec.m_fX + m_fY * rpVec.m_fY + m_fZ * rpVec.m_fZ + m_fW * rpVec.m_fW);
};

//////////////////////////////////////////////////////////////////////////
//		Sets the X and Y vectors
//////////////////////////////////////////////////////////////////////////
void oVector4::SetVector(float a_fX, float a_fY, float a_fZ, float a_fT){

	m_fX = a_fX;
	m_fY = a_fY;
	m_fZ = a_fZ;
	m_fW = a_fT;

}

//////////////////////////////////////////////////////////////////////////
//		Fixes the computers aproximation problems
//////////////////////////////////////////////////////////////////////////
void oVector4::TinyValueFix(){

	if(m_fX < .001 && m_fX > -.001)
		m_fX = 0;

	if(m_fY < .001 && m_fY > -.001)
		m_fY = 0;

	if(m_fZ < .001 && m_fZ > -.001)
		m_fZ = 0;

	if(m_fW < .001 && m_fW > -.001)
		m_fW = 0;
}

//////////////////////////////////////////////////////////////////////////
//		Noramlizes the vector
//////////////////////////////////////////////////////////////////////////
oVector4 oVector4::Normalise(){

	oVector4 pDummy;

	float fMag = Magnitude();

	pDummy.SetVector(m_fX / fMag, m_fY / fMag, m_fZ / fMag, m_fW / fMag);

	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		Gets the magnitude of the vector
//////////////////////////////////////////////////////////////////////////
float oVector4::Magnitude(){

	return sqrt(pow(m_fX, 2) + pow(m_fY, 2) + pow(m_fZ, 2) + pow(m_fW, 2));

}

//////////////////////////////////////////////////////////////////////////
//		returns the crossproduct
//////////////////////////////////////////////////////////////////////////
oVector4 oVector4::CrossProduct(oVector4 & rpVec){

	oVector4 pDummy;

	pDummy.SetVector(m_fY * rpVec.m_fZ - m_fZ * rpVec.m_fY,
					 m_fZ * rpVec.m_fX - m_fX * rpVec.m_fZ,
					 m_fX * rpVec.m_fY - m_fY * rpVec.m_fX,
					0);

	return pDummy;
}

//////////////////////////////////////////////////////////////////////////
//		Deconstructor
//////////////////////////////////////////////////////////////////////////
oVector4::~oVector4(){

}


//////////////////////////////////////////////////////////////////////////
//		oMatrix3x3 constructor
//////////////////////////////////////////////////////////////////////////
oMatrix3x3::oMatrix3x3(){

}

//////////////////////////////////////////////////////////////////////////
//		Makes one vector equal to another
//////////////////////////////////////////////////////////////////////////
void oMatrix3x3::operator=(oMatrix3x3 & rpMat){
		pRowOne = rpMat.pRowOne;
		pRowTwo = rpMat.pRowTwo;
		pRowThree = rpMat.pRowThree;
	};

//////////////////////////////////////////////////////////////////////////
//		Multiplies one vector to another
//////////////////////////////////////////////////////////////////////////
void oMatrix3x3::operator*=(oMatrix3x3 & rpMat){
		*this = *this * rpMat;
	};

//////////////////////////////////////////////////////////////////////////
//		Returns a Matrix that is the result of two matricies multiplied together
//////////////////////////////////////////////////////////////////////////
oMatrix3x3 oMatrix3x3::operator*(oMatrix3x3 & rpMat){
		oMatrix3x3 pDummy;
		oMatrix3x3 pSetter;

		//Setting each pRow of Dummy to be the columns of rpMat
		pDummy.pRowOne.SetVector(rpMat.pRowOne.m_fX, rpMat.pRowTwo.m_fX, rpMat.pRowThree.m_fX);
		pDummy.pRowTwo.SetVector(rpMat.pRowOne.m_fY, rpMat.pRowTwo.m_fY, rpMat.pRowThree.m_fY);
		pDummy.pRowThree.SetVector(rpMat.pRowOne.m_fZ, rpMat.pRowTwo.m_fZ, rpMat.pRowThree.m_fZ);

		//Setting time (multiplying the vectors returns the dot product)
		pSetter.pRowOne.SetVector(pRowOne * pDummy.pRowOne, pRowOne * pDummy.pRowTwo, pRowOne * pDummy.pRowThree);
		pSetter.pRowTwo.SetVector(pRowTwo * pDummy.pRowOne, pRowTwo * pDummy.pRowTwo, pRowTwo * pDummy.pRowThree);
		pSetter.pRowThree.SetVector(pRowThree * pDummy.pRowOne, pRowThree * pDummy.pRowTwo, pRowThree * pDummy.pRowThree);

		return pSetter;

};

//////////////////////////////////////////////////////////////////////////
//		Scales a matrix by an amount
//////////////////////////////////////////////////////////////////////////
void oMatrix3x3::ScaleMatrix(float a_fScale){
		oMatrix3x3 pDummy;

		pDummy.pRowOne.SetVector(a_fScale, 0 , 0);
		pDummy.pRowTwo.SetVector(0, a_fScale, 0);
		pDummy.pRowThree.SetVector(0, 0, a_fScale);

		*this *= pDummy;

	}

//////////////////////////////////////////////////////////////////////////
//		roatates a matrix by degrees
//////////////////////////////////////////////////////////////////////////
oMatrix3x3 oMatrix3x3::RotateMatrixDegrees(float a_fDegrees){

	return RotateMatrixRadians(a_fDegrees * DegreesToRadians);

}

//////////////////////////////////////////////////////////////////////////
//		roatates a matrix by radians
//////////////////////////////////////////////////////////////////////////
oMatrix3x3 oMatrix3x3::RotateMatrixRadians(float a_fRadians){

	oMatrix3x3 pDummy;

	pDummy.pRowOne.SetVector(cos(a_fRadians), -sin(a_fRadians), 0);
	pDummy.pRowTwo.SetVector(sin(a_fRadians), cos(a_fRadians), 0);
	pDummy.pRowThree.SetVector(0, 0, 1);

	pDummy.pRowOne.TinyValueFix();
	pDummy.pRowTwo.TinyValueFix();
	pDummy.pRowThree.TinyValueFix();

	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		Vector Transformation
//////////////////////////////////////////////////////////////////////////
oVector3 oMatrix3x3::TransformVector(oVector3 & rpVec){

	oVector3 pDummy;

	pDummy.SetVector((rpVec.m_fX * pRowOne.m_fX + rpVec.m_fY * pRowOne.m_fY + rpVec.m_fZ * pRowOne.m_fZ), (rpVec.m_fX * pRowTwo.m_fX + rpVec.m_fY * pRowTwo.m_fY + rpVec.m_fZ * pRowTwo.m_fZ), (rpVec.m_fX * pRowThree.m_fX + rpVec.m_fY * pRowThree.m_fY + rpVec.m_fZ * pRowOne.m_fZ));
	
	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		Deconstructor
//////////////////////////////////////////////////////////////////////////
oMatrix3x3::~oMatrix3x3(){
	
}


//////////////////////////////////////////////////////////////////////////
//		oMatrix4x4 constructor
//////////////////////////////////////////////////////////////////////////
oMatrix4x4::oMatrix4x4(){

	pRowOne.SetVector(1,0,0,0);
	pRowTwo.SetVector(0,1,0,0);
	pRowThree.SetVector(0,0,1,0);
	pRowFour.SetVector(0,0,0,1);

}

//////////////////////////////////////////////////////////////////////////
//		Makes one matrix equal to another
//////////////////////////////////////////////////////////////////////////
void oMatrix4x4::operator=(oMatrix4x4 & rpMat){
		pRowOne = rpMat.pRowOne;
		pRowTwo = rpMat.pRowTwo;
		pRowThree = rpMat.pRowThree;
		pRowFour = rpMat.pRowFour;
	};

//////////////////////////////////////////////////////////////////////////
//		Multiplies one matrix to another
//////////////////////////////////////////////////////////////////////////
void oMatrix4x4::operator*=(oMatrix4x4 & rpMat){
		*this = *this * rpMat;
	};

//////////////////////////////////////////////////////////////////////////
//		Returns a Matrix that is the result of two matricies multiplied together
//////////////////////////////////////////////////////////////////////////
oMatrix4x4 oMatrix4x4::operator*(oMatrix4x4 & rpMat){
		oMatrix4x4 pDummy;
		oMatrix4x4 pSetter;

		//Setting each pRow of Dummy to be the columns of rpMat
		pDummy.pRowOne.SetVector(rpMat.pRowOne.m_fX, rpMat.pRowTwo.m_fX, rpMat.pRowThree.m_fX, rpMat.pRowFour.m_fX);
		pDummy.pRowTwo.SetVector(rpMat.pRowOne.m_fY, rpMat.pRowTwo.m_fY, rpMat.pRowThree.m_fY, rpMat.pRowFour.m_fY);
		pDummy.pRowThree.SetVector(rpMat.pRowOne.m_fZ, rpMat.pRowTwo.m_fZ, rpMat.pRowThree.m_fZ, rpMat.pRowFour.m_fZ);
		pDummy.pRowFour.SetVector(rpMat.pRowOne.m_fW, rpMat.pRowTwo.m_fW, rpMat.pRowThree.m_fW, rpMat.pRowFour.m_fW);

		//Setting time (multiplying the vectors returns the dot product
		pSetter.pRowOne.SetVector(pRowOne * pDummy.pRowOne, pRowOne * pDummy.pRowTwo, pRowOne * pDummy.pRowThree, pRowOne * pDummy.pRowFour);
		pSetter.pRowTwo.SetVector(pRowTwo * pDummy.pRowOne, pRowTwo * pDummy.pRowTwo, pRowTwo * pDummy.pRowThree, pRowTwo * pDummy.pRowFour);
		pSetter.pRowThree.SetVector(pRowThree * pDummy.pRowOne, pRowThree * pDummy.pRowTwo, pRowThree * pDummy.pRowThree, pRowThree * pDummy.pRowFour);
		pSetter.pRowFour.SetVector(pRowFour * pDummy.pRowOne, pRowFour * pDummy.pRowTwo, pRowFour * pDummy.pRowThree, pRowFour * pDummy.pRowFour);

		return pSetter;

	};

//////////////////////////////////////////////////////////////////////////
//		Scales a matrix by an amount
//////////////////////////////////////////////////////////////////////////
void oMatrix4x4::ScaleMatrix(float a_fScale){
		oMatrix4x4 pDummy;

		pDummy.pRowOne.SetVector(a_fScale, 0 , 0, 0);
		pDummy.pRowTwo.SetVector(0, a_fScale, 0, 0);
		pDummy.pRowThree.SetVector(0, 0, a_fScale, 0);
		pDummy.pRowFour.SetVector(0, 0, 0, a_fScale);

		*this *= pDummy;

	}

//////////////////////////////////////////////////////////////////////////
//		roatates a matrix by degrees
//////////////////////////////////////////////////////////////////////////
oMatrix4x4 oMatrix4x4::RotateMatrixDegrees(float a_fDegrees){

	return RotateMatrixRadians(a_fDegrees * DegreesToRadians);

}

//////////////////////////////////////////////////////////////////////////
//		roatates a matrix by radians
//////////////////////////////////////////////////////////////////////////
oMatrix4x4 oMatrix4x4::RotateMatrixRadians(float a_fRadians){

	oMatrix4x4 pDummyOne;
	oMatrix4x4 pDummyTwo;

	pDummyOne.pRowOne.SetVector(1, 0, 0, 0);
	pDummyOne.pRowTwo.SetVector(0, cos(a_fRadians), -sin(a_fRadians),0);
	pDummyOne.pRowThree.SetVector(0, sin(a_fRadians), cos(a_fRadians), 0);
	pDummyOne.pRowFour.SetVector(0,0,0,1);

	pDummyOne.pRowOne.TinyValueFix();
	pDummyOne.pRowTwo.TinyValueFix();
	pDummyOne.pRowThree.TinyValueFix();
	pDummyOne.pRowFour.TinyValueFix();

	pDummyTwo.pRowOne.SetVector(cos(a_fRadians), 0, sin(a_fRadians), 0);
	pDummyTwo.pRowTwo.SetVector(0,1,0,0);
	pDummyTwo.pRowThree.SetVector(-sin(a_fRadians), 0, cos(a_fRadians), 0);
	pDummyTwo.pRowFour.SetVector(0,0,0,1);

	pDummyTwo.pRowOne.TinyValueFix();
	pDummyTwo.pRowTwo.TinyValueFix();
	pDummyTwo.pRowThree.TinyValueFix();
	pDummyTwo.pRowFour.TinyValueFix();

	pDummyOne *= pDummyTwo;

	pDummyTwo.pRowOne.SetVector(cos(a_fRadians), -sin(a_fRadians), 0, 0);
	pDummyTwo.pRowTwo.SetVector(sin(a_fRadians),cos(a_fRadians),0,0);
	pDummyTwo.pRowThree.SetVector(0, 0, 1, 0);
	pDummyTwo.pRowFour.SetVector(0,0,0,1);

	pDummyTwo.pRowOne.TinyValueFix();
	pDummyTwo.pRowTwo.TinyValueFix();
	pDummyTwo.pRowThree.TinyValueFix();
	pDummyTwo.pRowFour.TinyValueFix();

	pDummyOne *= pDummyTwo;

	return pDummyOne;

}

//////////////////////////////////////////////////////////////////////////
//		Creates an Orthrgraphic projection Matrix
//////////////////////////////////////////////////////////////////////////
oMatrix4x4 oMatrix4x4::OrthographicProjectionMatrix(float a_fXMin, float a_fXMax, float a_fYMin, float a_fYMax, float a_fZMin, float a_fZMax){

	oMatrix4x4 pDummy;

	pDummy.pRowOne.SetVector(2/(a_fXMax - a_fXMin), 0, 0, 0);
	pDummy.pRowTwo.SetVector(0, 2/(a_fYMin - a_fYMax), 0, 0);
	pDummy.pRowThree.SetVector(0, 0, -1/(a_fZMax - a_fZMin), 0);
	pDummy.pRowFour.SetVector(-(a_fXMax + a_fXMin)/(a_fXMax - a_fXMin), -(a_fYMin + a_fYMax)/(a_fYMin - a_fYMax), a_fZMin/(a_fZMax - a_fZMin), 1);

	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		Point Transformation
//////////////////////////////////////////////////////////////////////////
oVector3 oMatrix4x4::TransformPoint(oVector3 & rpVec){

	oVector3 pDummy;
	float fW = 0;

	pDummy.SetVector((rpVec.m_fX * pRowOne.m_fX + rpVec.m_fY * pRowOne.m_fY + rpVec.m_fZ * pRowOne.m_fZ + pRowOne.m_fW), (rpVec.m_fX * pRowTwo.m_fX + rpVec.m_fY * pRowTwo.m_fY + rpVec.m_fZ * pRowTwo.m_fZ + pRowTwo.m_fW), (rpVec.m_fX * pRowThree.m_fX + rpVec.m_fY * pRowThree.m_fY + rpVec.m_fZ * pRowOne.m_fZ + pRowThree.m_fW));
	
	fW = (rpVec.m_fX * pRowFour.m_fX + rpVec.m_fY * pRowFour.m_fY + rpVec.m_fZ * pRowFour.m_fZ + pRowFour.m_fW);

	if(fW != 1 && fW != 0){
		pDummy.SetVector(pDummy.m_fX / fW, pDummy.m_fY / fW, pDummy.m_fZ / fW);
	}
	
	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		Vector Transformation
//////////////////////////////////////////////////////////////////////////
oVector3 oMatrix4x4::TransformVector(oVector3 & rpVec){

	oVector3 pDummy;

	pDummy.SetVector((rpVec.m_fX * pRowOne.m_fX + rpVec.m_fY * pRowOne.m_fY + rpVec.m_fZ * pRowOne.m_fZ), (rpVec.m_fX * pRowTwo.m_fX + rpVec.m_fY * pRowTwo.m_fY + rpVec.m_fZ * pRowTwo.m_fZ), (rpVec.m_fX * pRowThree.m_fX + rpVec.m_fY * pRowThree.m_fY + rpVec.m_fZ * pRowOne.m_fZ));
	
	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		Deconstructor
//////////////////////////////////////////////////////////////////////////
oMatrix4x4::~oMatrix4x4(){

}


//////////////////////////////////////////////////////////////////////////
//		Constructor
//////////////////////////////////////////////////////////////////////////
oHex::oHex(){

}

//////////////////////////////////////////////////////////////////////////
//		Makes one Hex class equal to another using hexadecimal values
//////////////////////////////////////////////////////////////////////////
void oHex::operator=(oHex & rpHex){

		m_sRed = rpHex.m_sRed;
		m_sGreen = rpHex.m_sGreen;
		m_sBlue = rpHex.m_sBlue;
		m_fAlpha = rpHex.m_fAlpha;

		m_pColorValue = ConvertFromHex();

		ConvertToPercent();

	};

//////////////////////////////////////////////////////////////////////////
//		Makes one Hex class equal to another using intager values
//////////////////////////////////////////////////////////////////////////
void oHex::operator=(oVector4 & rpVec){

		m_pColorValue = rpVec;

		ConvertToHex();

		ConvertToPercent();
	};

//////////////////////////////////////////////////////////////////////////
//		makes sure the string length is 2 by adding a 0 or resizing the string to 2
//////////////////////////////////////////////////////////////////////////
void oHex::StringChecker(std::string & a_rsStr){

	char cSecondValue;

	if(a_rsStr.length() == 0){

		a_rsStr.resize(2);

		a_rsStr.front() = '0';
		a_rsStr.back() = '0';

	}

	if(a_rsStr.length() == 1){

		cSecondValue = a_rsStr[0];

		a_rsStr.resize(2);

		a_rsStr.front() = '0';
		a_rsStr.back() = cSecondValue;

	}

	if(a_rsStr.length() > 2)
		a_rsStr.resize(2);

	SingleConverter(a_rsStr);

}

//////////////////////////////////////////////////////////////////////////
//		Sets the hex class using hexadecimnal input
//////////////////////////////////////////////////////////////////////////
void oHex::SetHex(std::string a_sRed, std::string a_sGreen, std::string a_sBlue, float a_fAlpha){

	StringChecker(a_sRed);
	StringChecker(a_sGreen);
	StringChecker(a_sBlue);

	m_sRed = a_sRed;
	m_sGreen = a_sGreen;
	m_sBlue = a_sBlue;
	m_fAlpha = a_fAlpha;

	m_pColorValue = ConvertFromHex();

	ConvertToPercent();

}

//////////////////////////////////////////////////////////////////////////
//		Sets the hex class using integer input
//////////////////////////////////////////////////////////////////////////
void oHex::SetHex(int a_iRed, int a_iGreen, int a_iBlue, float a_fAlpha){

	if(a_iRed > 255)
		a_iRed = 255;
	if(a_iRed < 0)
		a_iRed = 0;
	if(a_iGreen > 255)
		a_iGreen = 255;
	if(a_iGreen < 0)
		a_iGreen = 0;
	if(a_iBlue > 255)
		a_iBlue = 255;
	if(a_iBlue < 0)
		a_iBlue = 0;
	if(a_fAlpha > 1)
		a_fAlpha = 1;
	if(a_fAlpha < 0)
		a_fAlpha = 0;

	m_pColorValue.SetVector(a_iRed, a_iGreen, a_iBlue, a_fAlpha);

	ConvertToHex();

	ConvertToPercent();

}

//////////////////////////////////////////////////////////////////////////
//		Converts a single string into an integer value
//////////////////////////////////////////////////////////////////////////
float oHex::SingleConverter(std::string & a_rsStr){

	int iValues[2];
	int iFinal = 0;

	for(int i = 0; i < 2; i++){

		if(a_rsStr[i] == '0')
			iValues[i] = 0;

		else if(a_rsStr[i] == '1')
			iValues[i] = 1;

		else if(a_rsStr[i] == '2')
			iValues[i] = 2;

		else if(a_rsStr[i] == '3')
			iValues[i] = 3;

		else if(a_rsStr[i] == '4')
			iValues[i] = 4;

		else if(a_rsStr[i] == '5')
			iValues[i] = 5;

		else if(a_rsStr[i] == '6')
			iValues[i] = 6;

		else if(a_rsStr[i] == '7')
			iValues[i] = 7;

		else if(a_rsStr[i] == '8')
			iValues[i] = 8;

		else if(a_rsStr[i] == '9')
			iValues[i] = 9;

		else if(a_rsStr[i] == 'A' || a_rsStr[i] == 'a')
			iValues[i] = 10;

		else if(a_rsStr[i] == 'B' || a_rsStr[i] == 'b')
			iValues[i] = 11;

		else if(a_rsStr[i] == 'C' || a_rsStr[i] == 'c')
			iValues[i] = 12;

		else if(a_rsStr[i] == 'D' || a_rsStr[i] == 'd')
			iValues[i] = 13;

		else if(a_rsStr[i] == 'E' || a_rsStr[i] == 'e')
			iValues[i] = 14;

		else if(a_rsStr[i] == 'F' || a_rsStr[i] == 'f')
			iValues[i] = 15;

		else{
			iValues[i] = 0;
			if(i == 0)
				a_rsStr.front() = '0';
			else
				a_rsStr.back() = '0';
		}

	}

	iFinal = (iValues[0] * 16) + iValues[1];

	return iFinal;

}

//////////////////////////////////////////////////////////////////////////
//		Converts a single int (from 0 - 15) into a char for hexadecimal values
//////////////////////////////////////////////////////////////////////////
std::string oHex::SingleConverter(int a_iIn){

	int iFront = 0;
	int iBack = 0;
	char cSetter;
	cSetter = '0';

	iFront = a_iIn / 16;

	iBack = a_iIn - (iFront * 16);

	std::string sDummy;
	sDummy.resize(2);

	for(int i = 0; i < 2; i++){
	if((iFront == 0 && i == 0) || (iBack == 0 && i == 1))
		cSetter = '0';

	if((iFront == 1 && i == 1) || (iBack == 1 && i == 1))
		cSetter = '1';

	if((iFront == 2 && i == 0) || (iBack == 2 && i == 1))
		cSetter = '2';

	if((iFront == 3 && i == 0) || (iBack == 3 && i == 1))
		cSetter = '3';

	if((iFront == 4 && i == 0) || (iBack == 4 && i == 1))
		cSetter = '4';

	if((iFront == 5 && i == 0) || (iBack == 5 && i == 1))
		cSetter = '5';

	if((iFront == 6 && i == 0) || (iBack == 6 && i == 1))
		cSetter = '6';

	if((iFront == 7 && i == 0) || (iBack == 7 && i == 1))
		cSetter = '7';

	if((iFront == 8 && i == 0) || (iBack == 8 && i == 1))
		cSetter = '8';

	if((iFront == 9 && i == 0) || (iBack == 9 && i == 1))
		cSetter = '9';

	if((iFront == 10 && i == 0) || (iBack == 10 && i == 1))
		cSetter = 'A';

	if((iFront == 11 && i == 0) || (iBack == 11 && i == 1))
		cSetter = 'B';

	if((iFront == 12 && i == 0) || (iBack == 12 && i == 1))
		cSetter = 'C';

	if((iFront == 13 && i == 0) || (iBack == 13 && i == 1))
		cSetter = 'D';

	if((iFront == 14 && i == 0) || (iBack == 14 && i == 1))
		cSetter = 'E';

	if((iFront == 15 && i == 0) || (iBack == 15 && i == 1))
		cSetter = 'F';

	if(i == 0)
		sDummy.front() = cSetter;
	else
		sDummy.back() = cSetter;
	}

	return sDummy;

}

//////////////////////////////////////////////////////////////////////////
//		COnverts integers into hexadecimal values
//////////////////////////////////////////////////////////////////////////
oVector4 oHex::ConvertFromHex(){

	oVector4 pDummy;

	pDummy.SetVector(SingleConverter(m_sRed), SingleConverter(m_sGreen), SingleConverter(m_sBlue), m_fAlpha);

	return pDummy;

}

//////////////////////////////////////////////////////////////////////////
//		Converts integers to hexadecimal values
//////////////////////////////////////////////////////////////////////////
void oHex::ConvertToHex(){

	m_sRed = SingleConverter(m_pColorValue.m_fX);

	m_sGreen = SingleConverter(m_pColorValue.m_fY);

	m_sBlue = SingleConverter(m_pColorValue.m_fZ);

	m_fAlpha = m_pColorValue.m_fW;

}

//////////////////////////////////////////////////////////////////////////
//		Converts the hex into a percentage for opengl
//////////////////////////////////////////////////////////////////////////
void oHex::ConvertToPercent(){

	m_pPercentValue.SetVector(m_pColorValue.m_fX / 255, m_pColorValue.m_fY / 255, m_pColorValue.m_fZ / 255, m_pColorValue.m_fW);

}

//////////////////////////////////////////////////////////////////////////
//		Deconstructor
//////////////////////////////////////////////////////////////////////////
oHex::~oHex(){

}