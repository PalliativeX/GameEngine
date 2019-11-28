#pragma once 

#include "Engine/Core/Window.h"
#include "Engine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Engine 
{

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps &props);

		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override
		{
			return data.width;
		}
		inline unsigned int getHeight() const override
		{
			return data.height;
		}

		inline void setEventCallback(const EventCallbackFn &callback) override
		{
			data.EventCallback = callback;
		}

		void setVSync(bool enabled) override;
		bool isVSyncEnabled() const override;

		inline virtual void* getNativeWindow() const { return window; };
	private:
		virtual void Init(const WindowProps &props);
		virtual void ShutDown();
	private:
		GLFWwindow *window;
		GraphicsContext* context;

		struct WindowData
		{
			std::string title;
			unsigned int width;
			unsigned int height;

			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData data;
	};

}