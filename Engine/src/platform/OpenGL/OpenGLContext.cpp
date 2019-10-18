#include "enginepch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Engine 
{

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

		ENGINE_LOG_INFO("OpenGL Info:");
		ENGINE_LOG_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		ENGINE_LOG_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		ENGINE_LOG_INFO(" Version: {0}", glGetString(GL_VERSION));

		#ifdef ENGINE_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			ENGINE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Engine requires at least OpenGL version 4.5!");
		#endif
	}


	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}

}