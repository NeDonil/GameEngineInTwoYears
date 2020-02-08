#include "Engine.h"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer() :
		Layer("Example")
	{

	}

	void OnUpdate() override
	{
		ENGINE_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Engine::Event& event) override
	{
		ENGINE_CLIENT_TRACE("{0}", 5);
	}
};

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};
Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}