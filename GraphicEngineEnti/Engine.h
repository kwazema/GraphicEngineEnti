#pragma once
class RenderModule;
#include "Modules/moduleManager.h"


class Engine
{
public:
	static Engine& get();

	RenderModule& getRender();
	

	bool start();
	void stop();
	void doFrame();
	void update();


private:
	RenderModule* render = nullptr;
	ModuleManager moduleManager;

	void registerAllModules();

};

