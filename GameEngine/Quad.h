#ifndef _QUAD_
#define _QUAD_

#include <GL\glew.h>
#include <GLLog.h>
#include <TextFileReader.h>

class Quad
{
public:
	Quad(void);
	~Quad(void);

	bool LoadVertShader(const char * filePath);
	bool LoadFragShader(const char * filePath);

	bool LinkShaders();

	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_EBO;
	
	GLuint m_FragmentShader;
	GLuint m_VertexShader;

	GLuint m_ShaderProgram;

	void Draw();
private:

};

#endif