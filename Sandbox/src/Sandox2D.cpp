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
	squareVA = Engine::VertexArray::create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Engine::Ref<Engine::VertexBuffer> squareVB;
	squareVB.reset(Engine::VertexBuffer::create(squareVertices, sizeof(squareVertices)));
	squareVB->setLayout({
		{ Engine::ShaderDataType::Float3, "position" }
		});
	squareVA->addVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Engine::Ref<Engine::IndexBuffer> squareIB;
	squareIB.reset(Engine::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	squareVA->setIndexBuffer(squareIB);

	flatColorShader = Engine::Shader::create("assets/shaders/flatColor.glsl");
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

	Engine::Renderer::beginScene(cameraController.getCamera());

	std::dynamic_pointer_cast<Engine::OpenGLShader>(flatColorShader)->bind();
	std::dynamic_pointer_cast<Engine::OpenGLShader>(flatColorShader)->uploadUniformFloat4("color", squareColor);

	Engine::Renderer::submit(flatColorShader, squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Engine::Renderer::endScene();
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