#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"

#include "Engine/ImGui/ImGuiLayer.h"

#include "Core/Timestep.h"

namespace Engine 
{

	class Application
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
		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> window;
		ImGuiLayer* imguiLayer;
		LayerStack layerStack;
		bool running = true;
		bool minimized = false;

		float lastFrameTime = 0.f;
	private:
		static Application *instance;
	};

	Application *createApplication();

}
