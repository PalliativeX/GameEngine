#include "enginepch.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

#include "Platform/OpenGL/OpenGLContext.h"

namespace Engine 
{

	static bool GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char *description) 
	{
		ENGINE_LOG_ERROR("GLFW Error ({0} : {1})", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps &props)
	{
		ENGINE_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ENGINE_PROFILE_FUNCTION();

		ShutDown();
	}

	Window *Window::create(const WindowProps &props)
	{
		return new WindowsWindow(props);
	}

	void WindowsWindow::Init(const WindowProps &props)
	{
		ENGINE_PROFILE_FUNCTION();

		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		ENGINE_LOG_INFO("Creating Window {0}, {1} {2}", props.title, props.width, props.height);

		if (!GLFWInitialized)
		{
			ENGINE_PROFILE_SCOPE("glfwCreateWindow");
			int success = glfwInit();
			ENGINE_ASSERT(success, "Could not initialized GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFWInitialized = true;
		}

		{
			ENGINE_PROFILE_SCOPE("glfwCreateWindow");
			window = glfwCreateWindow((int)data.width, (int)data.height, data.title.c_str(), nullptr, nullptr);
		}

		context = new OpenGLContext(window);
		context->init();

		glfwMakeContextCurrent(window);

		glfwSetWindowUserPointer(window, &data);
		setVSync(true);

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow *window)
		{
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
			}break;

			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
			}break;

			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
			}break;
			}
		});

		glfwSetCharCallback(window, [](GLFWwindow *window, unsigned int keycode)
		{
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods)
		{
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
			}break;

			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
			}break;
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow *window, double xOffset, double yOffset)
		{
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPos, double yPos)
		{
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::ShutDown()
	{
		ENGINE_PROFILE_FUNCTION();

		glfwDestroyWindow(window);
	}

	void WindowsWindow::onUpdate()
	{
		ENGINE_PROFILE_FUNCTION();

		glfwPollEvents();
		context->swapBuffers();
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