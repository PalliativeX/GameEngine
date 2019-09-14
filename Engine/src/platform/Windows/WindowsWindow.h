#pragma once 

#include "Engine/Window.h";
struct GLFWwindow;

namespace Engine {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps &props);

		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override
		{
			return m_Data.Width;
		}
		inline unsigned int getHeight() const override
		{
			return m_Data.Height;
		}

		inline void setEventCallback(const EventCallbackFn &callback) override
		{
			m_Data.EventCallback = callback;
		}

		void setVSync(bool enabled) override;
		bool isVSyncEnabled() const override;

		inline virtual void* getNativeWindow() const { return window; };
	private:
		virtual void Init(const WindowProps &props);
		virtual void ShutDown();
	private:
		GLFWwindow *window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;

			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}