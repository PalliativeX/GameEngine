#pragma once

#include "Engine.h"

class Sandbox2D : public Engine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(Engine::Timestep ts) override;
	virtual void onImGuiRender() override;
	void onEvent(Engine::Event& e) override;
private:
	Engine::OrthographicCameraController cameraController;

	// Temp
	Engine::Ref<Engine::VertexArray> squareVA;
	Engine::Ref<Engine::Shader> flatColorShader;

	Engine::Ref<Engine::Texture2D> texture;

	struct ProfileResult
	{
		const char* name;
		float time;
	};

	std::vector<ProfileResult> profileResults;

	glm::vec4 squareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};