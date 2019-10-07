#include "enginepch.h"
#include "Engine/Renderer/Renderer.h"

namespace Engine
{
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

	void Renderer::beginScene(OrthographicCamera& camera)
	{
		sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer::endScene()
	{

	}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->bind();
		shader->uploadUniformMat4("viewProjection", sceneData->viewProjectionMatrix);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}

}