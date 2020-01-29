#include "precompiledHeader.h"
#include "Engine.h"
#include "Render/RenderModule.h"

Engine& Engine::get()
{
	static Engine instance;
	return instance;
}

void Engine::start()
{
	
}

void Engine::stop()
{
}

void Engine::doFrame()
{
}
