#pragma once

#include "Core.h"
#include "events\Event.h"
#include "events\ApplicationEvent.h"
#include "Log.h"
#include "Window.h"

namespace Engine {

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	// to be defined in CLIENT
	Application* createApplication();

}
