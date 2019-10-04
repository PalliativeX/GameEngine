#include "enginepch.h"
#include "Engine/Renderer/Renderer.h"

namespace Engine
{

	void Renderer::beginScene()
	{

	}

	void Renderer::endScene()
	{

	}

	void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}

}