#include <Engine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer() : 
		Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition(0.f)

	{
		vertexArray.reset(Engine::VertexArray::create());

		float vertices[] = {
			-0.5f, -0.5f, 0.f,
			 0.5f, -0.5f, 0.f,
			 0.5f,  0.5f, 0.f,
			-0.5f,  0.5f, 0.f
		};

		std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::create(vertices, sizeof(vertices)));
		Engine::BufferLayout layout = {
			{ Engine::ShaderDataType::Float3, "position" }
		};
		vertexBuffer->setLayout(layout);
		vertexArray->addVertexBuffer(vertexBuffer);


		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Engine::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->setIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 position;

			uniform mat4 viewProjection;
			uniform mat4 model;
			
			void main()
			{
				gl_Position = viewProjection * model * vec4(position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			out vec4 fragColor;

			uniform vec3 color;
			
			void main()
			{
				fragColor = vec4(color, 1.0);
			}
		)";

		shader.reset(Engine::Shader::create(vertexSrc, fragmentSrc));
	}

	void onUpdate(Engine::Timestep ts) override
	{
		if (Engine::Input::isKeyPressed(ENGINE_KEY_LEFT)) {
			cameraPosition.x -= cameraMoveSpeed * ts;
		}
		else if (Engine::Input::isKeyPressed(ENGINE_KEY_RIGHT)) {
			cameraPosition.x += cameraMoveSpeed * ts;
		}
		if (Engine::Input::isKeyPressed(ENGINE_KEY_UP)) {
			cameraPosition.y += cameraMoveSpeed * ts;
		}
		else if (Engine::Input::isKeyPressed(ENGINE_KEY_DOWN)) {
			cameraPosition.y -= cameraMoveSpeed * ts;
		}
		if (Engine::Input::isKeyPressed(ENGINE_KEY_A)) {
			cameraRotation += cameraRotationSpeed;
		}
		if (Engine::Input::isKeyPressed(ENGINE_KEY_D)) {
			cameraRotation -= cameraRotationSpeed;
		}


		Engine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		Engine::RenderCommand::clear();

		camera.setPosition(cameraPosition);
		camera.setRotation(cameraRotation);

		Engine::Renderer::beginScene(camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->bind();
		std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->uploadUniformFloat3("color", squareColor);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.f);
				glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
				Engine::Renderer::submit(shader, vertexArray, transform);
			}
		}

		Engine::Renderer::endScene();
	}

	void onImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
		ImGui::End();
	}

	void onEvent(Engine::Event &event) override
	{
	}

private:
	std::shared_ptr<Engine::Shader> shader;
	std::shared_ptr<Engine::VertexArray> vertexArray;

	Engine::OrthographicCamera camera;
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
		pushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Engine::Application* Engine::createApplication()
{
	return new Sandbox();
}