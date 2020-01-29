#include "precompiledHeader.h"
#include "RenderModule.h"

bool RenderModule::init() 
{
	
	return initOpenGL();
}
void RenderModule::render()
{
	VertexDeclarationBuffer vbo(32,32);
	
	Shader vertex, fragment;
	
	vertex.init("Shader/data/vertexShader.vs",GL_VERTEX_SHADER);
	fragment.init("Shader/data/fragmentShader.fs",GL_FRAGMENT_SHADER);
	program = glCreateProgram();
	glAttachShader(program, vertex.getId());
	glAttachShader(program, fragment.getId());
	glLinkProgram(program);

	GLuint mvp_location, vpos_location, vcol_location;
	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");



	
	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(vertices), (void*)0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(vertices), (void*)(sizeof(float) * 2));


	glClearColor(0.21176470588235294, 0.7019607843137254
		, 0.8705882352941177, 1);

	while (!glfwWindowShouldClose(window->getWindowGL()))
	{
		float ratio;

		glm::mat4 m, mvp;
		glm::mat4 p;
		glfwGetFramebufferSize(window->getWindowGL(),
			&w,&h);
		ratio = w / (float)h;
		glViewport(0, 0, w, h);
	
		glClear(GL_COLOR_BUFFER_BIT);

		m = glm::identity<glm::mat4>();
		m = glm::translate(m, glm::vec3(0, 0, -3));
		
	
		
		p = glm::perspective(
			(float)glm::radians(90.0f),
			ratio,
			0.0f,
			500.0f
		); 
		
		
		
		//p = glm::translate(p, glm::vec3(0, 0, 5));
		//p = p * glm::lookAt(glm::vec3(0, 3, 5), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));
		//p = glm::rotate(p, (float)glfwGetTime(), glm::vec3(0, 1, 0));
	

		
	
		mvp = p * m;
		

		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const glm::float32*)&mvp);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);
		glfwSwapBuffers(window->getWindowGL());
		glfwPollEvents();
	}
	destroy();
}
void RenderModule::destroy()
{
	glfwDestroyWindow(window->getWindowGL());
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

RenderModule::RenderModule(WindowGLFW * w)
{
	assert(w);
	window = w;
	if (!init()) return;

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
