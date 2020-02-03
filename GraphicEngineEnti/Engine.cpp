#include "precompiledHeader.h"
#include "Engine.h"
#include "Modules/RenderModule.h"
#include "Modules/JoseModule.h"



Engine& Engine::get()
{
	static Engine instance;
	return instance;
}

RenderModule& Engine::getRender()
{
	assert(render);
	return *render;
	// TODO: insert return statement here
}

bool Engine::start()
{
	WindowGLFW*  window = new WindowGLFW(640, 480, "HELLO WORLD");
	render = new RenderModule(window);

	JoseModule * module = new JoseModule;

	moduleManager.registerModule(module);

	
	
	if (!render->init())
	{
		return false;
	}
	moduleManager.start();

	return true;
}

void Engine::stop()
{
	moduleManager.destroy();
	render->destroy();
	delete render;
}

void Engine::doFrame()
{
	update();
	moduleManager.render();
	render->render();
}

void Engine::update()
{

	float dt = 1.0f / 60.0f;
	
	moduleManager.update(dt);

	//std::this_thread::sleep_for
}

void Engine::registerAllModules()
{

}
