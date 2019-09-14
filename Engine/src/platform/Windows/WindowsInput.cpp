#include "enginepch.h"

#include "WindowsInput.h"

#include "Engine/Application.h"
#include <GLFW/glfw3.h>

namespace Engine {

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

		return { xPos, yPos };
	}

	float Engine::WindowsInput::getMouseXImpl()
	{
		auto[x, y] = getMousePositionImpl();
		return x;
	}

	float Engine::WindowsInput::getMouseYImpl()
	{
		auto[x, y] = getMousePositionImpl();
		return y;
	}

}