#include "enginepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Engine
{

	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();
}