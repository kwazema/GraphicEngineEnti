#include "precompiledHeader.h"
#include "JoseModule.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../Render/Mesh/tiny_obj_loader.h"



extern Mesh cube;
void JoseModule::loadTexture()
{

	 myTex  = ResourceManager::get().loadTexture("../GraphicEngineEnti/Render/Textures/data/wood.jpg");
	 //myTex = dynamic_cast<Texture*>(ResourceManager::get().loadTexture("../GraphicEngineEnti/Render/Textures/data/wood.jpg"));
}
void JoseModule::loadMesh()
{


	std::string inputfile = "cornell_box.obj";
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!warn.empty()) {
		std::cout << warn << std::endl;
	}

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	if (!ret) {
		exit(1);
	}

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
				tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
				tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
				tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
				tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
				tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
				// Optional: vertex colors
				// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
				// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
				// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
				
			}
			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}
}
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
	  loadTexture();
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
	
	cam->getTransform().setPosition(pos);


  }

  void JoseModule::renderDebug() 
  {
	   unsigned int  tex = myTex->getTexture();
	  glBindTexture(GL_TEXTURE_2D, tex);
	  Engine::get().setModelObjectConstants(quad1.asMatrix(), 
		  glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	  quad.activateAndRender();

	
	  
/*
	 Engine::get().setModelObjectConstants(quad2.asMatrix(), glm::vec4(1, 0, 0, 1));
	 quad.render();

	
	 Engine::get().setModelObjectConstants(quad3.asMatrix(), glm::vec4(1, 0, 0, 1));
	 quad.render();

	 Engine::get().setModelObjectConstants(cubetransform.asMatrix(), glm::vec4(1, 1, 1, 1.0f));
	 cube.activateAndRender();
	 */
  } 


JoseModule::JoseModule()
{
}


JoseModule::~JoseModule()
{
}
