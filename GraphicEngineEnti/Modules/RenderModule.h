#pragma once
#include "../Render/WindowGLFW.h"
#include "../Render/VertexDeclarationBuffer.h"
#include "../Shader/Shader.h"
#include "../Render/Camera.h"
#include "../Render/Mesh/Mesh.h"
#include "../Geometry/Transform.h"
#include "../Engine.h"
class RenderModule
{
	
private:
	Camera cam;
	bool initOpenGL() const;
	int w, h;
	GLuint program;
	WindowGLFW * window;
	GLuint mvp_location;
	glm::mat4 mvp;
	float lookAtval = 0.0f;

	void initRender();
public:
	RenderModule(WindowGLFW * w);
	~RenderModule();
	

	void setModelObjectConstants(const glm::mat4 model, const glm::vec4 color);
	
	bool attachShader(GLuint & shaderId);
	void useProgram();
	bool init();
	void render();
	void destroy();

	WindowGLFW * getCtxWindow();
};

