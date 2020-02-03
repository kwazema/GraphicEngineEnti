#pragma once
#include "../Modules/Module.h"
class JoseModule : public Module
{
public:

		virtual void start() override;
		virtual void stop() override;
		virtual void renderDebug() override;
		virtual void update(float elapsed)override;
	JoseModule();
	~JoseModule();
};

