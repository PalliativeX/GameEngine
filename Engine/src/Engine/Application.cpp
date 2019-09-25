#include "enginepch.h"

#include "Application.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"
#include "Engine/Input.h"

#include <GLAD/glad.h>

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

		imguiLayer = new ImGuiLayer();;
		pushOverlay(imguiLayer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);


		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.f,
			 0.5f, -0.5f, 0.f,
			 0.0f,  0.5f, 0.f
		};

		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		vertexBuffer->bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[3] = { 0, 1, 2 };
		indexBuffer.reset(IndexBuffer::create(indices, 3));
		indexBuffer->bind();

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 position;

			out vec3 Position;
			
			void main()
			{
				gl_Position = vec4(position + 0.4, 1.0);
				Position = (position + 0.4) * 0.5 + 0.5;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			out vec4 fragColor;

			in vec3 Position;
			
			void main()
			{
				fragColor = vec4(Position, 1.0);
			}
		)";

		shader.reset(new Shader(vertexSrc, fragmentSrc));
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
			glClearColor(0.15f, 0.15f, 0.15f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->bind();
			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

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

}
