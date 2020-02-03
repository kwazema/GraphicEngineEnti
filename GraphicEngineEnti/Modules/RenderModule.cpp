#include "precompiledHeader.h"
#include "RenderModule.h"
#include "../Render/Mesh/primitives.h"


extern Mesh quad;
bool RenderModule::init() 
{
	if (!initOpenGL()) return false;
	initRender();
	return true;
}


void RenderModule::render()
{
	
	Transform modelT;

	

		glClear(GL_COLOR_BUFFER_BIT);

		modelT.setPosition(glm::vec3(0, 0, -3));
		modelT.setScale(1.0f);
		
		cam.lookAt( glm::vec3(0, 1, 2), modelT.getPosition());
		

		/*for (auto& module : modules)
		{
			module.render();
		}*/
	
		setModelObjectConstants(modelT.asMatrix(), glm::vec4(1, 0, 0, 1));

	
		quad.activateAndRender();

		modelT.setPosition(glm::vec3(0, 1, -3));
		setModelObjectConstants(modelT.asMatrix(), glm::vec4(1, 0, 0, 1));
		quad.activateAndRender();

		modelT.setPosition(glm::vec3(0, -0.5, -1));
		modelT.setScale(2.5);
		glm::mat4 m = glm::identity<glm::mat4>();
		unsigned int transformLoc = glGetUniformLocation(program, "uColor");
		GLfloat vDiffuseColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	
		glUniform4fv(transformLoc, 1, (const GLfloat *)vDiffuseColor);
		float t = glfwGetTime();
		m = glm::rotate(m, t, glm::vec3(0, 1, 0));
		setModelObjectConstants( modelT.asMatrix() * m , glm::vec4(1, 0, 0, 1));
		quad.activateAndRender();

		glfwSwapBuffers(window->getWindowGL());
		glfwPollEvents();
	
	
}
void RenderModule::destroy()
{
	glfwDestroyWindow(window->getWindowGL());
	glfwTerminate();
	delete window;
	exit(EXIT_SUCCESS);
}

WindowGLFW * RenderModule::getCtxWindow()
{
	return window;
}

void RenderModule::initRender()
{
	createPrimitives();


	Shader vertex, fragment;

	vertex.init("Shader/data/vertexShader.vs", GL_VERTEX_SHADER);
	fragment.init("Shader/data/fragmentShader.fs", GL_FRAGMENT_SHADER);
	program = glCreateProgram();
	glAttachShader(program, vertex.getId());
	glAttachShader(program, fragment.getId());
	glLinkProgram(program);

	GLuint  vpos_location, vcol_location;
	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");


	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(VtxPosColor), (void*)0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(VtxPosColor), (void*)(sizeof(float) * 2));

	glfwGetFramebufferSize(window->getWindowGL(),
		&w, &h);

	cam.setProjectionParams((float)glm::radians(90.0f),
		w / h,
		0.0f,
		500.0f);


	glClearColor(0.21176470588235294, 0.7019607843137254
		, 0.8705882352941177, 1);

	glViewport(0, 0, w, h);
}

RenderModule::RenderModule(WindowGLFW * w)
{
	assert(w);
	window = w;


}
 static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_Q)
	{
	}
}

bool RenderModule::initOpenGL() const
{

	//TODO: ERROR CALLBACK DEVELOPMENT



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	if (window->getWindowGL() == nullptr)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
		return false;
	}

	
	glfwSetKeyCallback(window->getWindowGL(),key_callback);

	glfwMakeContextCurrent(window->getWindowGL());

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);


	return true;


}

RenderModule::~RenderModule()
{
}

void RenderModule::setModelObjectConstants(glm::mat4 model, glm::vec4 color)
{

	mvp = cam.getViewProjection() * model;
	glUseProgram(program);
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const glm::float32*) & mvp);
	
}

bool RenderModule::attachShader(GLuint & shaderId)
{
	//Check if shader have been already compiled
	glAttachShader(program, shaderId);

	return true;
}

void RenderModule::useProgram()
{
	glLinkProgram(program);
}
