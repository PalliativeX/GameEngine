#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"

#include "Engine/ImGui/ImGuiLayer.h"

#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffer.h"

namespace Engine 
{

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
		ImGuiLayer* imguiLayer;
		LayerStack layerStack;
		bool running = true;

		unsigned int vertexArray;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<VertexBuffer> vertexBuffer;
		std::unique_ptr<IndexBuffer> indexBuffer;

	private:
		static Application *instance;
	};

	Application *createApplication();

}
