#include "enginepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Engine 
{

	Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
	{
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);
		}

		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::create(const std::string & path)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:    
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
		case RendererAPI::API::OpenGL:  
			return CreateRef<OpenGLTexture2D>(path);
		}

		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}