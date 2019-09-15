#include "enginepch.h"

#include "Application.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"
#include "Engine/Input.h"

#include <GLAD/glad.h>

#include "Core.h"

namespace Engine {



	Application* Application::instance = nullptr;

	Application::Application()
	{
		ENGINE_ASSERT(!instance, "Application already exists")
		instance = this;

		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT(Application::onEvent));

		imguiLayer = new ImGuiLayer();;
		pushOverlay(imguiLayer);
	}

	Application::~Application()
	{
	}

	void Application::onEvent(Event &event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT(Application::onWindowClose));
		//ENGINE_LOG_TRACE(event.toString());
		for (auto it = layerStack.end(); it != layerStack.begin();)
		{
			(*--it)->onEvent(event);
			if (event.handled)
				break;
		}
	}

	void Application::pushLayer(Layer * layer)
	{
		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer * layer)
	{
		layerStack.pushOverlay(layer);
		layer->onAttach();
	}

	void Application::run()
	{
		while (running)
		{
			glClearColor(1, 0.5f, 0, 0.44f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer *layer : layerStack)
				layer->onUpdate();

			imguiLayer->begin();
			for (Layer* layer : layerStack)
				layer->onImGuiRender();
			imguiLayer->end();

			window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent &event) 
	{
		running = false;
		return true;
	}

	Application* createApplication()
	{
		return nullptr;
	}
}
