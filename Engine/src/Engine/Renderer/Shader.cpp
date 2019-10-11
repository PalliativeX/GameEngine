#include "enginepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine
{
	Shader * Shader::create(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		switch (Renderer::getAPI()) 
		{
			case RendererAPI::API::None:
				ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
