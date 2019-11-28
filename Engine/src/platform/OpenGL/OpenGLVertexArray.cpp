#include "enginepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Engine
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Engine::ShaderDataType::Float:    return GL_FLOAT;
		case Engine::ShaderDataType::Float2:   return GL_FLOAT;
		case Engine::ShaderDataType::Float3:   return GL_FLOAT;
		case Engine::ShaderDataType::Float4:   return GL_FLOAT;
		case Engine::ShaderDataType::Mat3:     return GL_FLOAT;
		case Engine::ShaderDataType::Mat4:     return GL_FLOAT;
		case Engine::ShaderDataType::Int:      return GL_INT;
		case Engine::ShaderDataType::Int2:     return GL_INT;
		case Engine::ShaderDataType::Int3:     return GL_INT;
		case Engine::ShaderDataType::Int4:     return GL_INT;
		case Engine::ShaderDataType::Bool:     return GL_BOOL;
		}

		ENGINE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		ENGINE_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() 
	{
		ENGINE_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &rendererID);
	}


	void OpenGLVertexArray::bind() const
	{
		ENGINE_PROFILE_FUNCTION();

		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::unbind() const
	{
		ENGINE_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		ENGINE_PROFILE_FUNCTION();

		ENGINE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(rendererID);
		vertexBuffer->bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.getComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.type), 
				element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), 
				(const void*)element.offset);
			index++;
		}

		vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		ENGINE_PROFILE_FUNCTION();

		glBindVertexArray(rendererID);
		indexBuffer->bind();

		this->indexBuffer = indexBuffer;
	}

}