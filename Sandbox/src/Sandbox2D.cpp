#include <chrono>
#include "Sandbox2D.h"
#include "Engine/Core/EntryPoint.h"

Sandbox2D::Sandbox2D():
	Layer("Layer2D"), m_CameraController((float)1280 / 720, true)
{
	ENGINE_PROFILE_FUNCTION();
}

void Sandbox2D::OnAttach()
{
	ENGINE_PROFILE_FUNCTION();
	
	m_CheckerboardTexture = Engine::Texture2D::Create("assets/textures/clown.png");

}

void Sandbox2D::OnDetach()
{
	ENGINE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Engine::Timestep ts)
{
	ENGINE_PROFILE_FUNCTION();

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

		Engine::Renderer2D::DrawQuad({ 2.0f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture);
		Engine::Renderer2D::DrawQuad({ 2.0f, -2.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture);

		Engine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ENGINE_PROFILE_FUNCTION();
	
	
	ImGui::Begin("Settings");

	auto stats = Engine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
	
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	ENGINE_PROFILE_FUNCTION();
	m_CameraController.OnEvent(e);
}
