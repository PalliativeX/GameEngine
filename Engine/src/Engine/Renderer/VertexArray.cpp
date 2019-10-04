#include "enginepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


namespace Engine 
{

	VertexArray* Engine::VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}