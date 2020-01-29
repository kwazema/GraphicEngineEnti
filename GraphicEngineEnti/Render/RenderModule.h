#pragma once
#include "WindowGLFW.h"
#include "../Render/VertexDeclarationBuffer.h"
#include "../Shader/Shader.h"
#include "Camera.h"
class RenderModule
{
private:
	Camera cam;
	bool initOpenGL() const;
	int w, h;
	GLuint program;
	WindowGLFW * window;
public:
	RenderModule(WindowGLFW * w);
	~RenderModule();

	bool attachShader(GLuint & shaderId);
	void useProgram();
	bool init();
	void render();
	void destroy();
};

