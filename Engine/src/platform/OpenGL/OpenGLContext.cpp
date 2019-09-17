#include "enginepch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Engine {
	OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle) :
		windowHandle(WindowHandle)
	{
		ENGINE_ASSERT(windowHandle, "Window Handle is null!");
	}


	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_ASSERT(status, "Failed to initialize Glad!");
	}


	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}

}