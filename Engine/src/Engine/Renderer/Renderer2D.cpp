#include "enginepch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> shader;
	};

	static Renderer2DStorage* data;


	void Renderer2D::init()
	{
		data = new Renderer2DStorage();
		data->quadVertexArray = VertexArray::create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));
		squareVB->setLayout({
			{ ShaderDataType::Float3, "position"}
			});
		data->quadVertexArray->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		data->quadVertexArray->setIndexBuffer(squareIB);

		data->shader = Shader::create("assets/shaders/flatColor.glsl");
	}

	void Renderer2D::shutdown()
	{
		delete data;
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(data->shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(data->shader)->uploadUniformMat4("viewProjection", camera.getViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(data->shader)->uploadUniformMat4("model", glm::mat4(1.f));
	}

	void Renderer2D::endScene()
	{

	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad({ position.x, position.y, 0.f }, size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(data->shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(data->shader)->uploadUniformFloat4("color", color);

		data->quadVertexArray->bind();
		RenderCommand::drawIndexed(data->quadVertexArray);
	}

}