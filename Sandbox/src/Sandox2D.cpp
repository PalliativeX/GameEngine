#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* _name, Fn&& _func) : name(_name), func(_func), stopped(false)
	{
		startTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!stopped)
			stop();
	}

	void stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		stopped = true;

		float duration = (end - start) * 0.001f;
		func({ name, duration });
	}
private:
	const char* name;
	Fn func;
	std::chrono::time_point<std::chrono::steady_clock> startTimepoint;
	bool stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { profileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), cameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::onAttach()
{
	texture = Engine::Texture2D::create("assets/textures/back.jpg");
}

void Sandbox2D::onDetach()
{
}

void Sandbox2D::onUpdate(Engine::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2D::onUpdate");

	// Update
	{
		PROFILE_SCOPE("CameraController::onUpdate");
		cameraController.onUpdate(ts);
	}

	// Render
	{
		PROFILE_SCOPE("Renderer Prep");
		Engine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Engine::RenderCommand::clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		Engine::Renderer2D::beginScene(cameraController.getCamera());

		Engine::Renderer2D::drawQuad({ -1.f, 0.f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.f });
		Engine::Renderer2D::drawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.2f, 0.9f, 1.f });
		Engine::Renderer2D::drawQuad({ 0.0f, 0.f, -0.1f }, { 10.f, 10.f }, texture);

		Engine::Renderer2D::endScene();
	}
}

void Sandbox2D::onImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
	ImGui::End();

	for (auto& result : profileResults)
	{
		char label[50];
		strcpy_s(label, "%.3fms ");
		strcat_s(label, result.name);
		ImGui::Text(label, result.time);
	}
	profileResults.clear();
}

void Sandbox2D::onEvent(Engine::Event& e)
{
	cameraController.onEvent(e);
}