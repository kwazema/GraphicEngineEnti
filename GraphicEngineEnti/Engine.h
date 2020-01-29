#pragma once
class RenderModule;
class Engine
{
public:
	static Engine& get();

	RenderModule& getRender();

	void start();
	void stop();
	void doFrame();
private:
	RenderModule* render = nullptr;

};

