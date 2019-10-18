#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application *Engine::createApplication();

int main(int argc, char **argv) 
{
	Engine::Log::init();

	auto app = Engine::createApplication();
	app->run();
	delete app;
}

#endif 
