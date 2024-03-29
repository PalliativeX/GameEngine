#include "enginepch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{

	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getAPI()) 
		{
		case RendererAPI::API::None :
				ENGINE_ASSERT(false, "RendererAPI::None is currently not supported.");
				return nullptr;
		case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}

		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
				ENGINE_ASSERT(false, "RendererAPI::None is currently not supported.");
				return nullptr;
		case RendererAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, size);
		}

		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


}