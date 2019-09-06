#pragma once

#include "Core.h"
#include "events\Event.h"
#include "events\ApplicationEvent.h"
#include "Log.h"
#include "Window.h"
#include "Engine\LayerStack.h"

namespace Engine {

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
	private:
		bool onWindowClose(WindowCloseEvent& e);


		std::unique_ptr<Window> window;
		bool running = true;
		LayerStack layerStack;
	};

	// to be defined in CLIENT
	Application* createApplication();

}
