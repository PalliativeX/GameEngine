#include "enginepch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace Engine
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string& Path)
		: path(Path)
	{
		int Width, Height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &Width, &Height, &channels, 0);
		ENGINE_ASSERT(data, "Failed to load image!");
		width = Width;
		height = Height;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, GL_RGB8, width, height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(rendererID, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererID);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, rendererID);
	}

}