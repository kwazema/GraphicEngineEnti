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
	  cam->getTransform().setPosition(0, 0, 8);
	  pos = cam->getPosition();
	front = glm::vec3(0, 0, 1);
  } 

  void JoseModule::stop() 
  {

	  delete cam;
  }

  void JoseModule::update(float elapsed)
  {
	
	  glm::vec3 euler = quad3.getEulerAngles();
	  quad1.setPosition(0.0f, 0.0f, 0.0f);

	  quad2.setPosition(glm::vec3(0, 1, -3));
	  float num = euler.y + glfwGetTime() * 10.0f;
	  quad2.setEulerAngles(euler.x, glm::radians(num), euler.z);

	  quad3.setPosition(glm::vec3(0, -0.5, -1));
	  quad3.setScale(2.5f);
	  quad3.setEulerAngles(glm::radians(euler.x + glfwGetTime()), euler.y, euler.z);

	  cubetransform.setPosition(glm::vec3(0, 0, 5));
	  cubetransform.setEulerAngles(glm::radians(euler.x + glfwGetTime()), euler.y, euler.z);

	  cameraController();
	 
	  //glm::vec3 front = cam->getFront();
	  cam->lookAt(pos,  target);
  }

  void JoseModule::cameraController()
  {
	  front = glm::vec3(0, 0, 1);
	  glm::vec3 euler = cam->getTransform().getEulerAngles();
	 


	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		newAngle +=glm::radians(5.0f) ;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		newAngle -= glm::radians(5.0f);
	}
	//cam->getTransform().yawPitchToVector(front ,newAngle, 0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pos -= 0.1f * cam->getFront();//cam->getFront();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pos += 0.1f * cam->getFront();
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		newPitch += glm::radians(5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		newPitch -= glm::radians(5.0f);
	}
	
		
	target = pos + glm::vec3( sinf(newAngle) * cosf(newPitch),
		sinf(newPitch), cosf(newAngle) * cosf(newPitch));
	glm::vec3 front = cam->getFront();
	//cam->getTransform().yawPitchToVector(front, newAngle, 0.0f);
	
	cam->getTransform().setPosition(pos);


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
