#include "enginepch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: projectionMatrix(glm::ortho(left, right, bottom, top, -1.f, 1.f)), viewMatrix(1.f), position(0.f)
	{
		ENGINE_PROFILE_FUNCTION();

		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
	{
		ENGINE_PROFILE_FUNCTION();

		projectionMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.f);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}


	void OrthographicCamera::recalculateViewMatrix()
	{
		ENGINE_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * 
			glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0, 0, 1));

		viewMatrix = glm::inverse(transform);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}


}