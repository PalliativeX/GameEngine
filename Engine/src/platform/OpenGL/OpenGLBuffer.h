#pragma once

#include "Engine/Renderer/Buffer.h"

namespace Engine
{

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;
	private:
		uint32_t rendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t Count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual uint32_t getCount() const { return count; }
	private:
		uint32_t rendererID;
		uint32_t count;
	};

}