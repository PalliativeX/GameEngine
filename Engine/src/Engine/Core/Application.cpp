#include "enginepch.h"

#include "Application.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Log.h"
#include "Input.h"

#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

#include "Core.h"

namespace Engine 
{

	Application* Application::instance = nullptr;


	Application::Application()
	{
		ENGINE_ASSERT(!instance, "Application already exists")
		instance = this;

		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT(Application::onEvent));

		Renderer::init();

		imguiLayer = new ImGuiLayer();;
		pushOverlay(imguiLayer);

	}

	Application::~Application()
	{
		//ENGINE_PROFILE_FUNCTION();

		//Renderer::shutdown();
	}

	void Application::onEvent(Event &event)
	{
		ENGINE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);

		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT(Application::onWindowClose));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT(Application::onWindowResize));

		for (auto it = layerStack.end(); it != layerStack.begin();)
		{
			(*--it)->onEvent(event);
			if (event.handled)
				break;
		}
	}

	void Application::pushLayer(Layer * layer)
	{
		ENGINE_PROFILE_FUNCTION();

		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer * layer)
	{
		ENGINE_PROFILE_FUNCTION();

		layerStack.pushOverlay(layer);
		layer->onAttach();
	}

	void Application::run()
	{
		ENGINE_PROFILE_FUNCTION();

		while (running)
		{
			ENGINE_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;

			if (!minimized) {
				for (Layer *layer : layerStack)
					layer->onUpdate(timestep);

				imguiLayer->begin();
				for (Layer* layer : layerStack)
					layer->onImGuiRender();
				imguiLayer->end();
			}

			window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e) 
	{
		running = false;
		return true;
	}

	bool Application::onWindowResize(WindowResizeEvent& e)
	{
		ENGINE_PROFILE_FUNCTION();

		if (e.getWidth() == 0 || e.getHeight() == 0) {
			minimized = true;
			return false;
		}

		minimized = false;
		Renderer::onWindowResize(e.getWidth(), e.getHeight());

		return false;
	}
}
