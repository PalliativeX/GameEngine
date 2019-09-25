#pragma once

namespace Engine
{

	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI getAPI() { return rendererAPI; }
	private:
		static RendererAPI rendererAPI;
	};
}