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
	
	m_GirlsheetTexture = Engine::Texture2D::Create("assets/game/textures/character_femalePerson_sheetHD.png");
	m_SpritesheetTexture = Engine::Texture2D::Create("assets/game/textures/spritesheet.png");

	m_SpriteStairs = Engine::SubTexture2D::GetFromCoords(m_SpritesheetTexture, { 1.0f, 11.0f }, { 128.0f, 128.0f });
	m_Animation = Engine::Animation2D::Create(m_GirlsheetTexture, { 0.0f, 0.0f }, { 192.0f, 256.0f }, 8, 0.1f);

	m_Animation->SetPosition({ 0.0, 0.0f, 1.0f});
	m_Animation->SetSize({ 1.0f, 1.0f });

	//m_SpriteMap['T'] = Engine::SubTexture2D::GetFromCoords(m_SpritesheetTexture, { 1.0f, 11.0f }, { 128.0f, 128.0f });
	//m_SpriteMap['D'] = Engine::SubTexture2D::GetFromCoords(m_SpritesheetTexture, { 6.0f, 11.0f }, { 128.0f, 128.0f });
	//m_SpriteMap['W'] = Engine::SubTexture2D::GetFromCoords(m_SpritesheetTexture, { 11.0f, 11.0f }, { 128.0f, 128.0f });
}

void Sandbox2D::OnDetach()
{
	ENGINE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Engine::Timestep ts)
{
	ENGINE_PROFILE_FUNCTION();

	m_Animation->OnUpdate(ts);

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

		//Engine::Renderer2D::DrawQuad({ 1.0f, -20.0f, 1.0f}, { 5.0f, 10.0f });

		Engine::Renderer2D::EndScene();

		m_Animation->Draw(m_CameraController.GetCamera());

#ifdef ACTIVE
		for (float y = 0.0f; y < 20.0f; y += 0.5f)
		{
			for (float x = 0.0f; x < 20.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
				Engine::Renderer2D::DrawQuad({ x,  y, 0.05f }, { 0.45, 0.45 }, color);
			}
		}

		Engine::Renderer2D::DrawRotatedQuad({ 10, 3, 0.1}, { 1.0f, 1.0f }, 30.0f, m_SquareColor);
		Engine::Renderer2D::DrawRotatedQuad({ 14, 3, 0.1}, { 1.0f, 1.0f }, 45.0f, m_SquareColor);
		Engine::Renderer2D::DrawRotatedQuad({ 18, 3, 0.1}, { 1.0f, 1.0f }, 60.0f, m_SquareColor);

		Engine::Renderer2D::DrawQuad(       { 4.0f,  5.0f, 0.15f }, { 0.5, 0.5 }, m_Texture);
		Engine::Renderer2D::DrawRotatedQuad({ 5.0f,  5.0f, 0.15f }, { 0.5, 0.5 }, 30.0f, m_Texture);
		Engine::Renderer2D::DrawRotatedQuad({ 6.0f,  5.0f, 0.15f }, { 0.5, 0.5 }, 45.0f, m_Texture);
		Engine::Renderer2D::DrawRotatedQuad({ 7.0f,  5.0f, 0.15f }, { 0.5, 0.5 }, 60.0f, m_Texture);
		Engine::Renderer2D::DrawRotatedQuad({ 8.0f,  5.0f, 0.15f }, { 0.5, 0.5 }, 90.0f, m_Texture);

#endif
	}
}

void Sandbox2D::OnImGuiRender()
{
	ENGINE_PROFILE_FUNCTION();
	ImGui::Begin("Square");

	auto stats = Engine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Total Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Total Index Count: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	ENGINE_PROFILE_FUNCTION();
	m_CameraController.OnEvent(e);
}
