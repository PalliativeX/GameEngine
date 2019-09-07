#include "enginepch.h"
#include "WindowsWindow.h"

#include "Engine/events/ApplicationEvent.h"
#include "Engine/events/KeyEvent.h"
#include "Engine/events/MouseEvent.h"

#include "glad/glad.h"

namespace Engine
{
	
	static bool GLFWinitialized = false;


	static void GLFWerrorCallBack(int error, const char* description)
	{
		ENGINE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

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
			glfwSetErrorCallback(GLFWerrorCallBack);
			GLFWinitialized = true;
		}
		window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_ASSERT(status, "Failed to initialized Glad!");
		glfwSetWindowUserPointer(window, &data);
		setVSync(true);

		// set GLFW callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int modes)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) 
			{
			case GLFW_PRESS :
			{
				KeyPressedEvent event(key, 0);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE :
			{
				KeyReleasedEvent event(key);
				data.eventCallback(event);
				break;
			}
			case GLFW_REPEAT :
			{
				KeyPressedEvent event(key, 1);
				data.eventCallback(event);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int modes)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS :
			{
				MouseButtonPressedEvent event(button);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE :
			{
				MouseButtonReleasedEvent event(button);
				data.eventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
		});
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