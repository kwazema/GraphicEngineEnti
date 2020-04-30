#include "precompiledHeader.h"
#include "SoncanModule.h"

extern Mesh cube;
extern Mesh Sphere;

void SoncanModule::start()
{
	cam = new Camera();

	glm::vec2 viewport = Engine::get().getRender().getViewport();

	cam->setProjectionParams((float)glm::radians(45.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	window = Engine::get().getRender().getCtxWindow()->getWindowGL();
	Engine::get().SetCamera(cam);
	//cam->getTransform().setPosition(0, 0, 0);
	cam->lookAt(glm::vec3(0, 50, 10), glm::vec3(0, 0, 0));

	pos = cam->getPosition();
	front = glm::vec3(0, 0, 1);
	initCameras();
}

void SoncanModule::stop()
{

	for (int i = 0; i < cameras.size(); i++)
		delete cameras[i];
}

void SoncanModule::update(float elapsed)
{
	float speedRotation = 25;
	float scaleMin = 1.5f;

	//---- Render Camera 0 (Static) ----//

	glm::vec3 euler = quad3.getEulerAngles();
	quad1.setPosition(-2.8f, 0.0f, 25.0f);

	quad4.getEulerAngles();
	quad4.setPosition(2.8f, 0.0f, 25.0f);

	cube1.setPosition(0.0f, 0.0f, 50.0f);
	cube1.setEulerAngles(glm::radians(euler.x + glfwGetTime() * speedRotation), (euler.y + glfwGetTime() * 2), euler.z);
	
	cube1.setScale(sin(glfwGetTime()) + scaleMin);
	

	//---- Render Camera 1 (Static) ----//

	speedRotation = 10;

	quad2.setPosition(0.0f, 0.0f, -20.f);
	quad2.setEulerAngles(euler.x, (euler.y + glfwGetTime() * speedRotation), euler.z);
	quad2.setScale(2);

	cube2.setPosition(0.0f, 10.0f, -50.0f);
	cube2.setEulerAngles(euler.x, (euler.y + glfwGetTime() * 2), euler.z);
	cube2.setScale(2.0f);

	cube3.setPosition(0.0f, -10.0f, -50.0f);
	cube3.setEulerAngles(euler.x, (euler.y + glfwGetTime() * 2), euler.z);
	cube3.setScale(2.0f);


	//---- Render Camera 0 (Dinamic) ----//

	quad3.setPosition(0, 50, 20);
	quad3.setScale(2.5f);
	quad3.setEulerAngles(glm::radians(euler.x + glfwGetTime()), euler.y, euler.z);





	//glm::vec3 front = cam->getFront();
	cameraController();
	cam->lookAt(pos, target);
}

void SoncanModule::initCameras()
{
	cameras.push_back(new Camera());
	cameras.push_back(new Camera());
	//cameras.push_back(new Camera());
	//cameras.push_back(new Camera());
	cameras.push_back(cam);
	glm::vec2 viewport = Engine::get().getRender().getViewport();
	cameras[0]->setProjectionParams((float)glm::radians(15.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[0]->lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 10), glm::vec3(0, 1, 0));

	cameras[1]->setProjectionParams((float)glm::radians(45.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[1]->lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -10), glm::vec3(0, 1, 0));

	//cameras[2]->setProjectionParams((float)glm::radians(45.0f),
	//	viewport.x / viewport.y,
	//	0.1f,
	//	500.0f);
	//cameras[2]->lookAt(glm::vec3(0, 90, 25), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//cameras[3]->setProjectionParams((float)glm::radians(120.0f),
	//	viewport.x / viewport.y,
	//	0.1f,
	//	500.0f);
	//cameras[3]->lookAt(glm::vec3(0, 5, 1.25), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	Engine::get().SetCamera(cameras[0]);
}

void SoncanModule::cameraController()
{
	front = glm::vec3(0, 0, 1);
	glm::vec3 euler = cam->getTransform().getEulerAngles();


	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		newAngle += glm::radians(5.0f);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		newAngle -= glm::radians(5.0f);
	//cam->getTransform().yawPitchToVector(front ,newAngle, 0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pos -= 0.1f * cam->getFront(); //cam->getFront();

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pos += 0.1f * cam->getFront();

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		newPitch += glm::radians(5.0f);

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		newPitch += glm::radians(-5.0f);

	if (canPress && glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		actualCamera++;
		actualCamera %= cameras.size();
		Engine::get().SetCamera(cameras[actualCamera]);
		canPress = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE)
	{
		canPress = true;
	}


	target = pos + glm::vec3(sinf(newAngle) * cosf(newPitch),
		sinf(newPitch), cosf(newAngle) * cosf(newPitch));
	glm::vec3 front = cam->getFront();

	cam->getTransform().setPosition(pos);

	std::cout << cam->getTransform().getPosition().x << " " 
			  << cam->getTransform().getPosition().y << " "
			  << cam->getTransform().getPosition().z << " "
		      << std::endl;
}


void SoncanModule::renderDebug()
{

	//---- Render Camera 0 (Static) ----//

	Engine::get().setModelObjectConstants(quad1.asMatrix(), glm::vec4(0.4f, 0.1f, 1.62f, 1.0f));
	quad.activateAndRender();

	Engine::get().setModelObjectConstants(cube1.asMatrix(), glm::vec4(0, 0, 0, 1.0f));
	cube.activateAndRender();

	Engine::get().setModelObjectConstants(quad4.asMatrix(), glm::vec4(0.4f, 0.1f, 1.62f, 1.0f));
	quad.activateAndRender();



	//---- Render Camera 1 (Static) ----//

	Engine::get().setModelObjectConstants(quad2.asMatrix(), glm::vec4(0.8f, 0.5f, 0.7f, 1));
	quad.render();

	Engine::get().setModelObjectConstants(cube2.asMatrix(), glm::vec4(0.5f, 0.8f, 0.3f, 1.0f));
	cube.activateAndRender();

	Engine::get().setModelObjectConstants(cube3.asMatrix(), glm::vec4(0.5f, 0.8f, 0.3f, 1.0f));
	cube.activateAndRender();



	//---- Render Camera 0 (Dinamic) ----//

	Engine::get().setModelObjectConstants(quad3.asMatrix(), glm::vec4(0.6f, 0 , 1, 1));
	quad.render();






	//cubetransform.setScale(1.0f);
	//Engine::get().setModelObjectConstants(cubetransform.asMatrix(), glm::vec4(1, 0, 1, 1.0f));
	//cube.render();
}


SoncanModule::SoncanModule()
{
}


SoncanModule::~SoncanModule()
{
}
