#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application *Engine::createApplication();

int main(int argc, char **argv) 
{
	Engine::Log::init();

	ENGINE_PROFILE_BEGIN_SESSION("Startup", "EngineProfile-Startup.json");
	auto app = Engine::createApplication();
	ENGINE_PROFILE_END_SESSION();

	ENGINE_PROFILE_BEGIN_SESSION("Runtime", "EngineProfile-Runtime.json");
	app->run();
	ENGINE_PROFILE_END_SESSION();

	ENGINE_PROFILE_BEGIN_SESSION("Shutdown", "EngineProfile-Shutdown.json");
	delete app;
	ENGINE_PROFILE_END_SESSION();
}

#endif 
