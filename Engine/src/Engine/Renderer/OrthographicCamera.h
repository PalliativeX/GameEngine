#pragma once

#include <glm/glm.hpp>

namespace Engine
{

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void setProjection(float left, float right, float bottom, float top);

		const glm::vec3 getPosition() { return position; }
		void setPosition(const glm::vec3& Position) { position = Position; recalculateViewMatrix(); }

		const float	getRotation() { return rotation; }
		void setRotation(float Rotation) { rotation = Rotation; recalculateViewMatrix(); }

		const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
		const glm::mat4& getViewMatrix() const { return viewMatrix; }
		const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix; }

	private:
		void recalculateViewMatrix();
	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

		glm::vec3 position;
		float rotation = 0.f;
	};
}