#include <chrono>
#include "Sandbox2D.h"
#include "Engine/Core/EntryPoint.h"
#include <box2d/box2d.h>

namespace Sandbox
{

	Sandbox2D::Sandbox2D() :
		Layer("Layer2D"), m_CameraController((float)1280 / 720, true)
	{
	}

	void Sandbox2D::OnAttach()
	{
		m_Texture = Engine::Texture2D::Create("assets/textures/clown.png");

		b2Vec2 gravity = { 0.0f, -9.81f };
		m_World = Engine::CreateScope<b2World>(gravity);

		b2BodyDef bodyDefs;
		bodyDefs.position.Set(0.0f, -10.0f);
		m_Ground = m_World->CreateBody(&bodyDefs);

		b2PolygonShape shape;
		shape.SetAsBox(50.0f, 10.0f);
		m_Ground->CreateFixture(&shape, 0.0f);

		for (int i = 0; i < 5; i++)
		{
			m_Boxes[i] = Box(m_World.get(), { i * 0.5f, 1 + i * 2.0f }, { 1.0f, 1.0f }, { 0.5f + i * 0.1, 0.5f + i * 0.1, 0.5f + i * 0.2, 1.0f });
		}
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

			for (int i = 0; i < 5; i++)
			{
				b2Vec2 position = m_Boxes[i].m_Body->GetPosition();
				glm::vec4 color = m_Boxes[i].m_Color;
				float angle = m_Boxes[i].m_Body->GetAngle();

				Engine::Renderer2D::DrawRotatedQuad({ position.x, position.y }, { 1.0f, 1.0f }, angle, color);
			}

			Engine::Renderer2D::DrawQuad({ -0.1f, -0.1f }, { 0.01f, 0.01f }, { 0.2f, 0.8f, 0.2f, 1.0f });
			Engine::Renderer2D::DrawQuad({ 0.1f, -0.1f }, { 0.01f, 0.01f }, { 0.2f, 0.8f, 0.2f, 1.0f });
			Engine::Renderer2D::DrawQuad({ 0.1f,  0.1f }, { 0.01f, 0.01f }, { 0.2f, 0.8f, 0.2f, 1.0f });
			Engine::Renderer2D::DrawQuad({ -0.1f,  0.1f }, { 0.01f, 0.01f }, { 0.2f, 0.8f, 0.2f, 1.0f });

			Engine::Renderer2D::EndScene();

			m_World->Step(1.0f / 60.0f, 8, 3);
		}
	}

	void Sandbox2D::OnImGuiRender()
	{

	}

	void Sandbox2D::OnEvent(Engine::Event& e)
	{
		m_CameraController.OnEvent(e);
	}

}