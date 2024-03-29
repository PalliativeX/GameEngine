#pragma once

#include "RendererAPI.h"

namespace Engine
{

	class RenderCommand
	{
	public:
		inline static void init()
		{
			rendererAPI->init();
		}

		inline static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			rendererAPI->setViewport(x, y, width, height);
		}

		inline static void setClearColor(const glm::vec4& color) { rendererAPI->setClearColor(color); }
		inline static void clear() { rendererAPI->clear(); }

		inline static void drawIndexed(const Ref<VertexArray>& vertexArray)
		{
			rendererAPI->drawIndexed(vertexArray);
		}

	private:
		static RendererAPI* rendererAPI;
	};

}