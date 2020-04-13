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
	m_CheckerboardTexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Texture = Engine::Texture2D::Create("assets/textures/icon.png");
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

	{
		ENGINE_PROFILE_SCOPE("Sandbox2D::Renderer prep");
		Engine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Engine::RenderCommand::Clear();
	}

	{
		ENGINE_PROFILE_SCOPE("Sandbox2D::Renderer draw");
		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (int i = 0; i < 100; i += 2)
		{
			Engine::Renderer2D::DrawQuad({ 0.0f,  i -0.0f },  { 3.0, 0.25 }, m_RedColor);
			Engine::Renderer2D::DrawQuad({ 0.0f,  i -0.25f }, { 3.0, 0.25 }, m_OrangeColor);
			Engine::Renderer2D::DrawQuad({ 0.0f,  i -0.50f }, { 3.0, 0.25 }, m_YellowColor);
			Engine::Renderer2D::DrawQuad({ 0.0f,  i -0.75f }, { 3.0, 0.25 }, m_GreenColor);
			Engine::Renderer2D::DrawQuad({ 0.0f,  i -1.0f },  { 3.0, 0.25 }, m_BlueColor);
			Engine::Renderer2D::DrawQuad({ 0.0f,  i -1.25f }, { 3.0, 0.25 }, m_PurpleColor);
		}

		Engine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ENGINE_PROFILE_FUNCTION();
	ImGui::Begin("Square");

	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
	ImGui::ColorEdit4("Red color", glm::value_ptr(m_RedColor));
	ImGui::ColorEdit4("Orange color", glm::value_ptr(m_OrangeColor));
	ImGui::ColorEdit4("Yellow color", glm::value_ptr(m_YellowColor));
	ImGui::ColorEdit4("Green color", glm::value_ptr(m_GreenColor));
	ImGui::ColorEdit4("Blue color", glm::value_ptr(m_BlueColor));
	ImGui::ColorEdit4("Square Purple", glm::value_ptr(m_PurpleColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	ENGINE_PROFILE_FUNCTION();
	m_CameraController.OnEvent(e);
}
