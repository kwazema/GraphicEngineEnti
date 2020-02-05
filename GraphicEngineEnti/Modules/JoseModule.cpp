#include "precompiledHeader.h"
#include "JoseModule.h"

extern Mesh cube;
  void JoseModule::start() 
  {
	  transform.setPosition(0.0f, -1.0f, -3.0f);

  } 

  void JoseModule::stop() 
  {

  }

  void JoseModule::renderDebug() 
  {
	  Engine::get().setModelObjectConstants(transform.asMatrix(), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	  quad.activateAndRender();

	  Transform modelT;
	  modelT.setPosition(glm::vec3(0, 0, -3));
	  modelT.setScale(1.0f);
	
	 

	 modelT.setPosition(glm::vec3(0, 1, -3));
	 Engine::get().setModelObjectConstants(modelT.asMatrix(), glm::vec4(1, 0, 0, 1));
	 quad.render();

	 modelT.setPosition(glm::vec3(0, -0.5, -1));
	 modelT.setScale(2.5);


	 glm::vec3 euler = modelT.getEulerAngles();
	 modelT.setEulerAngles(euler.x + glfwGetTime(), euler.y, euler.z);

	 Engine::get().setModelObjectConstants(modelT.asMatrix(), glm::vec4(1, 0, 0, 1));
	 quad.render();

	 //modelT.setRotation(glm::identity<glm::mat4>());
	 modelT.setPosition(glm::vec3(0, 0, 5));
	 Engine::get().setModelObjectConstants(modelT.asMatrix(), glm::vec4(1, 0, 0, 1));
	 cube.activateAndRender();

  } 
  void JoseModule::update(float elapsed) 
  {

  }

JoseModule::JoseModule()
{
}


JoseModule::~JoseModule()
{
}
