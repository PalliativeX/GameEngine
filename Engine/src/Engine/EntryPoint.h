#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::createApplication();

int main(int argc, char** argv)
{
	Engine::Log::init();
	Engine::Log::getCoreLogger()->warn("Initialized Log!");
	Engine::Log::getClientLogger()->info("Hello!");


	auto app = Engine::createApplication();
	app->run();
	delete app;
}

#endif