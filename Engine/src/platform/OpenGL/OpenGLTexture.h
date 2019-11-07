#pragma once

#include "Engine/Renderer/Texture.h"

#include <glad/glad.h>

namespace Engine
{

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t Width, uint32_t Height);
		OpenGLTexture2D(const std::string& Path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override { return width; }
		virtual uint32_t getHeight() const override { return height; }

		virtual void setData(void* data, uint32_t size) override;

		virtual void bind(uint32_t slot = 0) const override;

	private:
		std::string path;
		uint32_t width, height;
		uint32_t rendererID;
		GLenum internalFormat, dataFormat;
	};
}