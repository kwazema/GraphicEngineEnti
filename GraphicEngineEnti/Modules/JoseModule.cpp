#include "precompiledHeader.h"
#include "JoseModule.h"

extern Mesh cube;
  void JoseModule::start() 
  {
	 
	  cam = new Camera();
	  
      glm::vec2 viewport=  Engine::get().getRender().getViewport();
	  
	  cam->setProjectionParams((float)glm::radians(45.0f),
		  viewport.x / viewport.y,
		  0.1f,
		  500.0f);
	  window = Engine::get().getRender().getCtxWindow()->getWindowGL();
	  Engine::get().SetCamera(cam);
	  pos = cam->getPosition();
  } 

  void JoseModule::stop() 
  {

	  delete cam;
  }

  void JoseModule::update(float elapsed)
  {
	
	  glm::vec3 euler = cubetransform.getEulerAngles();
	  quad1.setPosition(0.0f, 0.0f, 0.0f);

	  quad2.setPosition(glm::vec3(0, 1, -3));
	  quad2.setEulerAngles(euler.x, euler.y + glfwGetTime(), euler.z);

	  quad3.setPosition(glm::vec3(0, -0.5, -1));
	  quad3.setScale(2.5f);
	  quad3.setEulerAngles(euler.x + glfwGetTime(), euler.y, euler.z);

	  cubetransform.setPosition(glm::vec3(0, 0, 5));
	  cubetransform.setEulerAngles(euler.x + glfwGetTime(), euler.y, euler.z);

	  cameraController();
	 
	  cam->lookAt(pos, pos + cam->getFront());
  }

  void JoseModule::cameraController()
  {
	  glm::vec3 euler = cam->getTransform().getEulerAngles();
	  float newAngle = euler.y;
	 if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
	{
		pos += 0.1f * glm::vec3(0, 0, -1);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pos += 0.1f * glm::vec3(0, 0, 1);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		
		newAngle += 5.0f ;
		
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		newAngle -= 5.0f;
	}

	cam->getTransform().setPosition(pos);
	cam->transform.setEulerAngles(euler.x,euler.y + glfwGetTime(), euler.z);
	std::cout << cam->getTransform().getEulerAngles().x << " " 
		<< cam->getTransform().getEulerAngles().y<< std::endl;
  }

  void JoseModule::renderDebug() 
  {
	
	  Engine::get().setModelObjectConstants(quad1.asMatrix(), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	  quad.activateAndRender();


	 Engine::get().setModelObjectConstants(quad2.asMatrix(), glm::vec4(1, 0, 0, 1));
	 quad.render();

	
	 Engine::get().setModelObjectConstants(quad3.asMatrix(), glm::vec4(1, 0, 0, 1));
	 quad.render();

	 Engine::get().setModelObjectConstants(cubetransform.asMatrix(), glm::vec4(1, 1, 1, 1.0f));
	 cube.activateAndRender();

  } 


JoseModule::JoseModule()
{
}


JoseModule::~JoseModule()
{
}
