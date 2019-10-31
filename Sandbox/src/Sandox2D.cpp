#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

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
	// Update
	cameraController.onUpdate(ts);

	// Render
	Engine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Engine::RenderCommand::clear();

	Engine::Renderer2D::beginScene(cameraController.getCamera());

	Engine::Renderer2D::drawQuad({ -1.f, 0.f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.f });
	Engine::Renderer2D::drawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.2f, 0.9f, 1.f });
	Engine::Renderer2D::drawQuad({ 0.0f, 0.f, -0.1f }, { 10.f, 10.f}, texture);

	Engine::Renderer2D::endScene();
}

void Sandbox2D::onImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
	ImGui::End();
}

void Sandbox2D::onEvent(Engine::Event& e)
{
	cameraController.onEvent(e);
}