#include <Engine.h>

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void onUpdate() override
	{
	
	}

	void onEvent(Engine::Event &event) override
	{
		// CLIENT_LOG_INFO(event.toString());
	}
};

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		pushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Engine::Application* Engine::createApplication()
{
	return new Sandbox();
}