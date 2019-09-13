#include "enginepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGl/ImGuiOpenGLRenderer.h"

#include "glfw/glfw3.h"
#include "glad/glad.h"

#include "Engine/Application.h"

namespace Engine {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::onAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 130");
	}

	void ImGuiLayer::onDetach()
	{
	}

	void ImGuiLayer::onUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());
		
		float Time = (float)glfwGetTime();
		io.DeltaTime = time > 0.0f ? (Time - time) : (1.0f / 60.0f);
		time = Time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImGuiLayer::onEvent(Event &event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT(ImGuiLayer::onMouseButtonPressedEvent));
		dispatcher.dispatch<MouseButtonReleasedEvent>(BIND_EVENT(ImGuiLayer::onMouseButtonReleasedEvent));
		dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT(ImGuiLayer::onMouseMovedEvent));
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT(ImGuiLayer::onMouseScrolledEvent));
		dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT(ImGuiLayer::onKeyPressedEvent));
		dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT(ImGuiLayer::onKeyReleasedEvent));
		dispatcher.dispatch<KeyTypedEvent>(BIND_EVENT(ImGuiLayer::onKeyTypedEvent));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT(ImGuiLayer::onWindowResizeEvent));

	}

	bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent & event)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.MouseDown[event.getMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent & event)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.MouseDown[event.getMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent & event)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.MousePos = ImVec2(event.getX(), event.getY());

		return false;
	}

	bool ImGuiLayer::onMouseScrolledEvent(MouseScrolledEvent & event)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.MouseWheel = event.getXOffset();
		io.MouseWheelH = event.getYOffset();

		return false;
	}

	bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent & event)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.KeysDown[event.getKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent & event)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.KeysDown[event.getKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::onKeyTypedEvent(KeyTypedEvent & event)
	{
		ImGuiIO &io = ImGui::GetIO();
		int keycode = event.getKeyCode();
		if (keycode > 0 && keycode < 0x10000)
		{
			io.AddInputCharacter(keycode);
		}

		return false;
	}

	bool ImGuiLayer::onWindowResizeEvent(WindowResizeEvent & event)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.getWidth(), event.getHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.getWidth(), event.getHeight());

		return false;
	}

}