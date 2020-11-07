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
		m_BoxTexture = Engine::Texture2D::Create("assets/textures/boxCartoon.png");

		m_CameraController.SetZoomLevel(6.25f);
		m_CameraController.SetPosition({ 5.0f, 4.0f, 0.0f });

		b2Vec2 gravity = { 0.0f, -9.81f };
		m_World = Engine::CreateScope<b2World>(gravity);

		b2BodyDef bodyDefs;
		bodyDefs.position.Set(0.0f, -10.0f);
		m_Ground = m_World->CreateBody(&bodyDefs);

		b2PolygonShape shape;
		shape.SetAsBox(50.0f, 10.0f);
		m_Ground->CreateFixture(&shape, 0.0f);

		for (int i = 0; i < 4; i++)
		{
			glm::vec2 position = { Engine::Random::Float() * 3.0f, 3.0f };
			glm::vec4 color = { Engine::Random::Float(), Engine::Random::Float(), Engine::Random::Float(), 1.0f };

			m_Boxes[m_BoxesCount++] = Box(m_World.get(), position, { 0.25f, 0.25f }, {0.2f, 0.5f, 0.8f, 1.0f});
		}

		for(int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				m_Boxes[m_BoxesCount++] = Box(m_World.get(), { j + i % 2, i }, { 0.25f, 0.25f }, {0.0f, 0.0f, 0.0f, 1.0f}, false);
			}
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

			for (int i = 0; i < m_BoxesCount; i++)
			{
				glm::vec2 position = m_Boxes[i].GetPosition();
				glm::vec2 size = m_Boxes[i].GetSize();
				glm::vec4 color = m_Boxes[i].GetColor();
				Engine::Ref<Engine::Texture2D> texture = m_Boxes[i].GetTexture();
				float angle = m_Boxes[i].GetAngle();

				if(texture != nullptr)
					Engine::Renderer2D::DrawRotatedQuad(position, size, glm::radians(angle), texture);
				else
					Engine::Renderer2D::DrawRotatedQuad(position, size, glm::radians(angle), color);
			}

			Engine::Renderer2D::DrawQuad({ 0.0f, -10.0f }, { 100.0f, 20.0f }, { 0.2f, 0.5f, 0.8f, 1.0f });

			Engine::Renderer2D::EndScene();

			if (m_BoxesCount < 500)
				m_Boxes[m_BoxesCount++] = Box(m_World.get(), { Engine::Random::Float() * 10.0, 30.0f }, { 0.25f, 0.25f }, m_BoxTexture);

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