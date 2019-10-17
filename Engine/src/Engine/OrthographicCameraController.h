#pragma once

#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Core/Timestep.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace Engine
{

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float AspectRatio, bool Rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		OrthographicCamera& getCamera() { return camera; }
		const OrthographicCamera& getCamera() const { return camera; }
	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizeEvent& e);
	private:
		float aspectRatio;
		float zoomLevel = 1.f;
		OrthographicCamera camera;

		bool rotation;

		glm::vec3 cameraPosition = { 0.f, 0.f, 0.f };
		float cameraRotation = 0.f;
		float cameraTranslationSpeed = 15.f, cameraRotationSpeed = 15.f;
	};
}