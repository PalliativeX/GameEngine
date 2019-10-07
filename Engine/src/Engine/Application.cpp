#include "enginepch.h"

#include "Application.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"
#include "Engine/Input.h"

#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/Renderer.h"

#include "Core.h"

namespace Engine 
{

	Application* Application::instance = nullptr;


	Application::Application()
		: camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		ENGINE_ASSERT(!instance, "Application already exists")
		instance = this;

		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT(Application::onEvent));

		imguiLayer = new ImGuiLayer();;
		pushOverlay(imguiLayer);

		vertexArray.reset(VertexArray::create());

		float vertices[] = {
			-0.75f, -0.75f, 0.f,
			 0.75f, -0.75f, 0.f,
			 0.75f,  0.75f, 0.f,
			-0.75f,  0.75f, 0.f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "position" }
		};
		vertexBuffer->setLayout(layout);
		vertexArray->addVertexBuffer(vertexBuffer);


		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->setIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 position;

			out vec3 Position;


			uniform mat4 viewProjection;
			
			void main()
			{
				gl_Position = viewProjection * vec4(position, 1.0);
				Position = position * 0.9f + 0.2f;
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
			RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
			RenderCommand::clear();

			camera.setRotation(45.f);

			Renderer::beginScene(camera);

			Renderer::submit(shader, vertexArray);

			Renderer::endScene();

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
