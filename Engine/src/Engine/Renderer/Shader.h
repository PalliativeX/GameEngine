#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Engine 
{

	class Shader
	{
	public: 
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void bind() const;
		void unbind() const;

		void uploadUniformMat4(const std::string& name, const glm::mat4 matrix);
		void uploadUniformVec3(const std::string& name, const glm::vec3 vector);
	private:
		uint32_t rendererID;
	};
}