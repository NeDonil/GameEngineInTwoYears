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
		//ENGINE_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Engine::Event& event) override
	{
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
};

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Engine::ImGuiLayer());
	}

	~Sandbox()
	{
	}
};
Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}