#ifndef _SPRITE_H_
#define _SPRITE_H_

//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Sprites.h
//		@details		The Sprite and Animation Class'
//		@author			Derek Potter
//		@date created	2/19/2014
//////////////////////////////////////////////////////////////////////////

#include "Utilities.h"
#include "Quad.h"
#include <SOIL.h>

//////////////////////////////////////////////////////////////////////////
//		@Class:		oSprite
//		@Details:	A class to handle sprites
//////////////////////////////////////////////////////////////////////////
class oSprite: public Quad
{
public:
	oSprite(void);
	~oSprite(void);
oSprite( const char* a_pTexture, int a_iWidth, int a_iHeight, oVector4 a_v4Color,GLFWwindow* );
	void Draw();
	
	void SetVertexData( Vertex* a_vertexData );
	const Vertex* GetVertexData() const;

	oVector3 m_v3Position;

	GLFWwindow * GameWindow;

	oVector2 m_v2Scale;

	unsigned int m_uiTexture;

private:
	
	Vertex m_aoVerts[4];

	oMatrix4x4 * modelMatrix;

	
	oVector4 m_v4SpriteColor;

	oVector2 m_minUVCoords;
	oVector2 m_maxUVCoords;
	oVector2 m_uvScale;
	oVector2 m_uvOffset;	

	unsigned int m_uSourceBlendMode;
	unsigned int m_uDestinationBlendMode;
	int tex_loc;
	int matrix_location;
	int proj_location;

};

inline void	oSprite::SetVertexData( Vertex* a_vertexData )
{
	memcpy( &m_aoVerts, a_vertexData, sizeof(Vertex) * 4 );
}

inline const Vertex* oSprite::GetVertexData() const
{
	return static_cast<const Vertex*>( m_aoVerts );
}


class oRender{

public:

	oRender();
	~oRender();
 
	int RenderStartUp();

	void RenderLoopStart();
	void RenderLoopEnd();

	GLFWwindow* window;

};

#endif
