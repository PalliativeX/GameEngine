#include "enginepch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> textureShader;
		Ref<Texture2D> whiteTexture;
	};

	static Renderer2DStorage* data;


	void Renderer2D::init()
	{
		data = new Renderer2DStorage();
		data->quadVertexArray = VertexArray::create();

		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.f, 0.f,
			 0.5f, -0.5f, 0.0f, 1.f, 0.f,
			 0.5f,  0.5f, 0.0f, 1.f, 1.f,
			-0.5f,  0.5f, 0.0f, 0.f, 1.f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));
		squareVB->setLayout({
			{ ShaderDataType::Float3, "position"},
			{ ShaderDataType::Float2, "texCoord"}
			});
		data->quadVertexArray->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		data->quadVertexArray->setIndexBuffer(squareIB);

		data->whiteTexture = Texture2D::create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		data->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

		data->textureShader= Shader::create("assets/shaders/texture.glsl");
		data->textureShader->setInt("texture", 0);
	}

	void Renderer2D::shutdown()
	{
		delete data;
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera)
	{
		data->textureShader->bind();
		data->textureShader->setMat4("viewProjection", camera.getViewProjectionMatrix());
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
		data->textureShader->setFloat4("color", color);
		data->whiteTexture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		data->textureShader->setMat4("transform", transform);

		data->quadVertexArray->bind();
		RenderCommand::drawIndexed(data->quadVertexArray);
	}

	void Renderer2D::drawQuad(const glm::vec2 & position, const glm::vec2 & size, const Ref<Texture2D>& texture)
	{
		drawQuad({ position.x, position.y, 0.f }, size, texture);
	}

	void Renderer2D::drawQuad(const glm::vec3 & position, const glm::vec2 & size, const Ref<Texture2D>& texture)
	{
		data->textureShader->setFloat4("color", glm::vec4(1.f));
		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		data->textureShader->setMat4("transform", transform);

		data->quadVertexArray->bind();
		RenderCommand::drawIndexed(data->quadVertexArray);
	}

}