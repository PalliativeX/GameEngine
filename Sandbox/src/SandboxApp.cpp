#include <Engine.h>
#include <Engine/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer() : 
		Layer("Example"), cameraController(1280.f / 720.f, true)

	{
		vertexArray = Engine::VertexArray::create();

		float vertices[] = {
			-0.5f, -0.5f, 0.f, 0.f, 0.f,
			 0.5f, -0.5f, 0.f, 1.f, 0.f,
			 0.5f,  0.5f, 0.f, 1.f, 1.f, 
			-0.5f,  0.5f, 0.f, 0.f, 1.f
		};

		std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::create(vertices, sizeof(vertices)));
		Engine::BufferLayout layout = {
			{ Engine::ShaderDataType::Float3, "position" },
			{ Engine::ShaderDataType::Float2, "texCoord" }
		};
		vertexBuffer->setLayout(layout);
		vertexArray->addVertexBuffer(vertexBuffer);


		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Engine::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->setIndexBuffer(indexBuffer);

		shader = shaderLibrary.load("assets/shaders/shader.glsl");

		texture = Engine::Texture2D::create("assets/textures/sun.jpg");
		texture->bind();

		logoTexture = Engine::Texture2D::create("assets/textures/protoss_yellow.png");
		logoTexture->bind();

		std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->bind();
		std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->uploadUniformInt("diffuse", 0);
	}

	void onUpdate(Engine::Timestep ts) override
	{
		// update
		cameraController.onUpdate(ts);

		// render
		Engine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		Engine::RenderCommand::clear();

		Engine::Renderer::beginScene(cameraController.getCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->bind();


		texture->bind();
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f - 0.7f, y * 0.11f - 0.7f, 0.f);
				glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
				Engine::Renderer::submit(shader, vertexArray, transform);
			}
		}

		logoTexture->bind();
		Engine::Renderer::submit(shader, vertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(2.f, 1.f, 0.f)));

		Engine::Renderer::endScene();
	}

	void onImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
		ImGui::End();
	}

	void onEvent(Engine::Event &e) override
	{
		cameraController.onEvent(e);
	}

private:
	Engine::ShaderLibrary shaderLibrary;
	std::shared_ptr<Engine::Shader> shader;
	std::shared_ptr<Engine::VertexArray> vertexArray;
	Engine::Ref<Engine::Texture2D> texture;
	Engine::Ref<Engine::Texture2D> logoTexture;

	Engine::OrthographicCameraController cameraController;
	glm::vec3 cameraPosition;
	float cameraRotation = 0.f;
	float cameraRotationSpeed = 10.f;
	float cameraMoveSpeed = 2.f;

	glm::vec3 squareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		//pushLayer(new ExampleLayer());
		pushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Engine::Application* Engine::createApplication()
{
	return new Sandbox();
}