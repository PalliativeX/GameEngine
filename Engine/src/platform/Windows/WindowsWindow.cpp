#include "enginepch.h"
#include "WindowsWindow.h"

namespace Engine
{
	
	static bool GLFWinitialized = false;


	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		init(props);
	}


	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}


	Window* Window::create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}


	void WindowsWindow::init(const WindowProps& props)
	{
		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		ENGINE_CORE_INFO("Creating window {0}, {1}, {2}", props.title, props.width, props.height);

		if (!GLFWinitialized) {
			int success = glfwInit();
			ENGINE_ASSERT(success, "Could not initialize GLFW!");

			GLFWinitialized = true;
		}
		window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		setVSync(true);
	}


	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(window);
	}


	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	void WindowsWindow::setVSync(bool enabled)
	{
		enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);
		data.VSync = enabled;
	}


	bool WindowsWindow::isVSyncEnabled() const
	{
		return data.VSync;
	}
}