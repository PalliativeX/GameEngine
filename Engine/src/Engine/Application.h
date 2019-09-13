#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"

namespace Engine {

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event &e);

		void pushLayer(Layer *layer);
		void pushOverlay(Layer *layer);

		static inline Application &get() { return *instance; }
		inline Window &getWindow() { return *window; }
	private:
		bool onWindowClose(WindowCloseEvent &event);

		std::unique_ptr<Window> window;
		LayerStack layerStack;
		bool running = true;

		static Application *instance;
	};

	Application *createApplication();

}
