#include "enginepch.h"

#include "WindowsInput.h"

#include "Engine/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Engine 
{

	Input* Input::instance = new WindowsInput();

	bool Engine::WindowsInput::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Engine::WindowsInput::isMousePressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> Engine::WindowsInput::getMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float Engine::WindowsInput::getMouseXImpl()
	{
		auto[x, y] = getMousePositionImpl();
		y;
		return x;
	}

	float Engine::WindowsInput::getMouseYImpl()
	{
		auto[x, y] = getMousePositionImpl();
		x;
		return y;
	}

}