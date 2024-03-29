#include "enginepch.h"
#include "OrthographicCameraController.h"

#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"

namespace Engine
{

	OrthographicCameraController::OrthographicCameraController(float AspectRatio, bool Rotation)
		: aspectRatio(AspectRatio), camera(-AspectRatio * zoomLevel, AspectRatio * zoomLevel, -zoomLevel, zoomLevel), rotation(Rotation)
	{ }

	void OrthographicCameraController::onUpdate(Timestep ts)
	{
		ENGINE_PROFILE_FUNCTION();

		if (Input::isKeyPressed(ENGINE_KEY_A)) {
			cameraPosition.x -= cameraTranslationSpeed * ts;
		}
		else if (Input::isKeyPressed(ENGINE_KEY_D)) {
			cameraPosition.x += cameraTranslationSpeed * ts;
		}
		if (Input::isKeyPressed(ENGINE_KEY_W)) {
			cameraPosition.y += cameraTranslationSpeed * ts;
		}
		else if (Input::isKeyPressed(ENGINE_KEY_S)) {
			cameraPosition.y -= cameraTranslationSpeed * ts;
		}

		if (rotation) {

			if (Input::isKeyPressed(ENGINE_KEY_Q)) {
				cameraRotation += cameraRotationSpeed;
			}
			if (Input::isKeyPressed(ENGINE_KEY_E)) {
				cameraRotation -= cameraRotationSpeed;
			}
			camera.setRotation(cameraRotation);
		}

		camera.setPosition(cameraPosition);

		cameraTranslationSpeed = zoomLevel;

	}

	void OrthographicCameraController::onEvent(Event & e)
	{
		ENGINE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT(OrthographicCameraController::onMouseScrolled));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT(OrthographicCameraController::onWindowResized));
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent & e)
	{
		ENGINE_PROFILE_FUNCTION();

		zoomLevel -= e.getYOffset() * 0.25f;
		zoomLevel = std::max(zoomLevel, 0.25f);
		camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent & e)
	{
		ENGINE_PROFILE_FUNCTION();

		aspectRatio = (float)e.getWidth() / (float)e.getHeight();
		camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

}