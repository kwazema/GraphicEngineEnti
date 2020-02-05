#pragma once
#include "../Modules/Module.h"
#include "../Render/Mesh/primitives.h"
#include "../Geometry/Transform.h"
#include "../Modules/RenderModule.h"
#include "../Render/Camera.h"
class JoseModule : public Module
{
private:
	Transform quad1,quad2,quad3,cubetransform;
	Camera * cam;
	GLFWwindow* window;
	glm::vec3 pos;
public:

		virtual void start() override;
		virtual void stop() override;
		virtual void renderDebug() override;
		virtual void update(float elapsed)override;

		void cameraController();


	JoseModule();
	~JoseModule();
};

