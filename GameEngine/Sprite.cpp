#include "Sprite.h"

oSprite::oSprite(void)
{
	//Default Shaders for Default constructor
	LoadVertShader("VertexShader.glsl");
	LoadFragShader("FragmentShader.glsl");
	LinkShaders();

}

oSprite::~oSprite(void)
{
}

oSprite::oSprite(const char* a_pTexture, int a_iWidth, int a_iHeight, oVector4 a_v4Color , GLFWwindow * window)
{

	GameWindow = window;
	//Default Shaders for Default constructor

	LoadVertShader("VertexShader.glsl");
	LoadFragShader("FragmentShader.glsl");
	LinkShaders();

	m_v2Scale = oVector2(a_iWidth, a_iHeight);
	m_v3Position = oVector3(0,0,0);

	modelMatrix = new oMatrix4x4();

	modelMatrix->pRowFour.m_fX = m_v3Position.m_fX;
	modelMatrix->pRowFour.m_fY = m_v3Position.m_fY;
	modelMatrix->pRowFour.m_fZ = m_v3Position.m_fZ;

	proj_location = glGetUniformLocation(m_ShaderProgram, "projection");

	m_v4SpriteColor = a_v4Color;

	m_aoVerts[0].Pos = oVector3(-0.5f,  0.5f,  0.0f);
	m_aoVerts[1].Pos = oVector3(0.5f,  0.5f,  0.0f);
	m_aoVerts[2].Pos = oVector3(-0.5f,  -0.5f,  0.0f);
	m_aoVerts[3].Pos = oVector3(0.5f,  -0.5f,  0.0f);
	
	
	m_aoVerts[0].Color = oVector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[1].Color = oVector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[2].Color = oVector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[3].Color = oVector4(1.0f,  1.0f,  1.0f, 1.0f);

	m_aoVerts[0].UV = oVector2(0.0f,  0.0f);
	m_aoVerts[1].UV = oVector2(0.0f,  1.0f);
	m_aoVerts[2].UV = oVector2(1.0f,  0.0f);
	m_aoVerts[3].UV = oVector2(1.0f,  1.0f);

	GLuint elements[] =
	{
		0,1,2,3
	};

	//Gen Buffers
	glGenBuffers(1,&m_VBO);
	glGenBuffers(1,&m_EBO);
	glGenVertexArrays(1, &m_VAO);

	//Bind Buffers
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	//Put Data into buffers
	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//Enable some attributes
	GLint posAttrib = glGetAttribLocation(m_ShaderProgram,"position");
	glEnableVertexAttribArray(posAttrib);
	GLint colAttrib = glGetAttribLocation(m_ShaderProgram,"color");
	glEnableVertexAttribArray(colAttrib);
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);


	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	glBindVertexArray(0);

	matrix_location = glGetUniformLocation(m_ShaderProgram, "matrix");

	m_uiTexture = 0;
	m_minUVCoords = oVector2( 0.f, 0.f );
	m_maxUVCoords = oVector2( 1.f, 1.f );
	m_uvScale = oVector2( 1.f, 1.f );
	m_uvOffset = oVector2( 0.f, 0.f );

	m_uSourceBlendMode	= GL_SRC_ALPHA;
	m_uDestinationBlendMode = GL_ONE_MINUS_SRC_ALPHA;

	glGenTextures(1, &m_uiTexture);
	glActiveTexture (GL_TEXTURE0);

	int width, height;
	unsigned char* image = SOIL_load_image(a_pTexture, &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture( GL_TEXTURE_2D,m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	tex_loc = glGetUniformLocation (m_ShaderProgram, "diffuseTexture");
	glUseProgram (m_ShaderProgram);
	glUniform1i (tex_loc, 0); // use active texture 0

}

void oSprite::Draw()
{
	glBlendFunc (m_uSourceBlendMode, m_uDestinationBlendMode);
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i (tex_loc, 0); 
	
	modelMatrix->pRowOne.m_fX = m_v2Scale.m_fX;
	modelMatrix->pRowTwo.m_fY = m_v2Scale.m_fY;
	modelMatrix->pRowFour.m_fX = m_v3Position.m_fX;
	modelMatrix->pRowFour.m_fY = m_v3Position.m_fY;
	modelMatrix->pRowFour.m_fZ = m_v3Position.m_fZ;

	oMatrix4x4 MVP = (*modelMatrix * *Ortho);

	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, &MVP.pRowOne.m_fX);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);


	glDrawElements(GL_TRIANGLE_STRIP, 4,GL_UNSIGNED_INT,0);	
}


oRender::oRender(){
	glfwSetTime(.0f);
}

oRender::~oRender(){

}

int oRender::RenderStartUp(){

			//setup to log some GLFW stuff

	char message[256];
	sprintf (message, "starting GLFW %s", glfwGetVersionString ());
	assert (gl_log (message, __FILE__, __LINE__));
	glfwSetErrorCallback (glfw_error_callback);

	//open an OS window using GLFW
	if(!glfwInit())
	{
		fprintf (stderr,"ERROR: could not start GLFW3\n");
		return 1;
	}

	//Anti-Aliasing
	glfwWindowHint (GLFW_SAMPLES, 4);

	//get the primary monitor
	GLFWmonitor* mon = glfwGetPrimaryMonitor ();
	//this lets us the the video mode for the monitor we pass
	const GLFWvidmode* vmode = glfwGetVideoMode (mon);
	window = glfwCreateWindow (
		vmode->width, vmode->height, "Extended GL Init",NULL, NULL
		);
	glfwSetWindowSize(window, g_gl_width, g_gl_height);

	if (!window) {
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	//start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

	Ortho = new oMatrix4x4();

	Orthographic(0,g_gl_width,g_gl_height, 0, 0, -1, Ortho);

}

void oRender::RenderLoopStart(){

	glEnable (GL_CULL_FACE); // cull face
		glCullFace (GL_BACK); // cull back face
		glFrontFace (GL_CW); // GL_CCW for counter clock-wise

		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//resize window
		glViewport (0, 0, g_gl_width, g_gl_height);

		g_TimeFromStart = glfwGetTime();
		g_DeltaTime = g_TimeFromStart - g_PreviousTime;
		g_PreviousTime = g_TimeFromStart;
		//g_DeltaTime /= 10;

}

void oRender::RenderLoopEnd(){
	// update other events like input handling 
		glfwPollEvents ();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (window);


		//When do i exit?
		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (window, 1);
		}
}