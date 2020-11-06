#include <chrono>
#include "Sandbox2D.h"
#include "Engine/Core/EntryPoint.h"
#include <box2d/box2d.h>

Sandbox2D::Sandbox2D():
	Layer("Layer2D"), m_CameraController((float)1280 / 720, true)
{
}

void Sandbox2D::OnAttach()
{
	
	m_Texture = Engine::Texture2D::Create("assets/textures/clown.png");
	b2World* world;

}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Engine::Timestep ts)
{
	{
		ENGINE_PROFILE_SCOPE("Sandbox2D::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	Engine::Renderer2D::ResetStats();
	{
		ENGINE_PROFILE_SCOPE("Sandbox2D::Renderer prep");
		Engine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Engine::RenderCommand::Clear();
	}

	{
		ENGINE_PROFILE_SCOPE("Sandbox2D::Renderer draw");
		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, {0.2f, 0.5f, 0.8f, 1.0f});
		Engine::Renderer2D::DrawQuad({ 0.0f, -2.0f }, { 1.0f, 1.0f }, { 0.5f, 0.2f, 0.8f, 1.0f });

		Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, { 0.8f, 0.5f, 0.2f, 1.0f });

		Engine::Renderer2D::DrawQuad({ 2.0f, 0.0f }, { 1.0f, 1.0f }, m_Texture);
		Engine::Renderer2D::DrawQuad({ 2.0f, -2.0f }, { 1.0f, 1.0f }, m_Texture);

		Engine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{	
	
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	m_CameraController.OnEvent(e);
}
