#include "enginepch.h"
#include "Application.h"

#include "GLFW\glfw3.h"

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT_FN(onEvent));
	}


	Application::~Application()
	{

	}


	void Application::pushLayer(Layer* layer)
	{
		layerStack.pushLayer(layer);
	}


	void Application::pushOverlay(Layer* overlay)
	{
		layerStack.pushOverlay(overlay);
	}


	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		for (auto it = layerStack.end(); it != layerStack.begin(); ) {
			(*--it)->onEvent(e);
			if (e.handled)
				break;
		}
	}


	void Application::run()
	{

		while (running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layerStack)
				layer->onUpdate();

			window->onUpdate();

		}
	}


	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		running = false;
		return true;
	}

}