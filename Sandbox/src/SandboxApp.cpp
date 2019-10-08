#include <Engine.h>

#include "ImGui/imgui.h"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer() : 
		Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition(0.f)

	{
		vertexArray.reset(Engine::VertexArray::create());

		float vertices[] = {
			-0.75f, -0.75f, 0.f,
			0.75f, -0.75f, 0.f,
			0.75f,  0.75f, 0.f,
			-0.75f,  0.75f, 0.f
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

			out vec3 Position;


			uniform mat4 viewProjection;
			
			void main()
			{
				gl_Position = viewProjection * vec4(position, 1.0);
				Position = position * 0.9f + 0.2f;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			out vec4 fragColor;

			in vec3 Position;

			
			void main()
			{
				fragColor = vec4(Position, 1.0);
			}
		)";

		shader.reset(new Engine::Shader(vertexSrc, fragmentSrc));
	}

	void onUpdate() override
	{
		if (Engine::Input::isKeyPressed(ENGINE_KEY_LEFT)) {
			cameraPosition.x -= cameraMoveSpeed;
		}
		else if (Engine::Input::isKeyPressed(ENGINE_KEY_RIGHT)) {
			cameraPosition.x += cameraMoveSpeed;
		}
		if (Engine::Input::isKeyPressed(ENGINE_KEY_UP)) {
			cameraPosition.y += cameraMoveSpeed;
		}
		else if (Engine::Input::isKeyPressed(ENGINE_KEY_DOWN)) {
			cameraPosition.y -= cameraMoveSpeed;
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

		Engine::Renderer::submit(shader, vertexArray);

		Engine::Renderer::endScene();
	}

	void onImGuiRender() override
	{

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
	float cameraRotationSpeed = 2.5f;
	float cameraMoveSpeed = 0.1f;
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