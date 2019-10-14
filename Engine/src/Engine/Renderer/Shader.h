#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Engine 
{

	class Shader
	{
	public: 
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Shader* create(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Shader* create(const std::string& filepath);
	};
}