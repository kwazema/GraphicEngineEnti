#pragma once
#include "../Modules/Module.h"
#include "../Render/Mesh/primitives.h"
#include "../Geometry/Transform.h"
#include "../Modules/RenderModule.h"
class JoseModule : public Module
{
private:
	Transform transform;
public:

		virtual void start() override;
		virtual void stop() override;
		virtual void renderDebug() override;
		virtual void update(float elapsed)override;
	JoseModule();
	~JoseModule();
};

