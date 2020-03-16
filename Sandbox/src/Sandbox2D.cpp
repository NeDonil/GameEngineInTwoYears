#include "Sandbox2D.h"
#include "Engine/Core/EntryPoint.h"

Sandbox2D::Sandbox2D():
	Layer("Layer2D"), m_CameraController((float)1280 / 720)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Texture = Engine::Texture2D::Create("assets/textures/icon.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Engine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Engine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	Engine::RenderCommand::Clear();

	Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8, 0.8 }, { 0.2, 0.3, 0.8f, 1.0f });
	Engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5, 0.75 }, m_SquareColor);
	Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
	Engine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	m_CameraController.OnEvent(e);
}
