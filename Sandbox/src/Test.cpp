#include "Test.h"

Test::Test()
	: m_CameraController((float)1280 / (float)720)
{

}

void Test::OnAttach()
{

	
#endif
	Engine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	m_TankTexture = Engine::Texture2D::Create("assets/textures/tank2.png");
	m_BulletTexture = Engine::Texture2D::Create("assets/textures/bullet.png");
	m_CheckerboardTexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");

	AddBox(Box({ 2.0f, 2.0f }, { 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }));
}

void Test::OnDetach()
{

	
#endif
}

void Test::OnUpdate(Engine::Timestep ts)
{

	
#endif
	m_CameraController.OnUpdate(ts);

	Clear();
	Render();
	Logic(ts);
}

void Test::OnEvent(Engine::Event& event)
{

	
#endif
	m_CameraController.OnEvent(event);
}

void Test::OnImGuiRender()
{

	
#endif
	ImGui::Text("Bullet Direction: (%f, %f)", m_Bullet.Direction.x, m_Bullet.Direction.y);
	ImGui::Text("Bullet Life: %f", m_Bullet.Life);
	ImGui::Text("Bullet Position: (%f, %f)", m_Bullet.Position.x, m_Bullet.Position.y);
	ImGui::Text("Bullet Rotation: %f", m_Bullet.Rotation);
	ImGui::Text("Bullet Speed: %f", m_Bullet.Speed);

	ImGui::Text("Box Count: %d", m_Boxes.size());
}

void Test::Render()
{

	
#endif
	Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Engine::Renderer2D::DrawQuad({ -50.0f, -50.0f, 0.1f }, { 100.0f, 100.0f }, m_CheckerboardTexture, 40.0f);

	Engine::Renderer2D::DrawRotatedQuad({ m_TankPosition.x, m_TankPosition.y, 0.2f }, { 0.2f, 0.2f }, m_TankRotation, m_TankTexture);
	if (m_Bullet.Life > 0.0f)
		Engine::Renderer2D::DrawRotatedQuad({ m_Bullet.Position.x, m_Bullet.Position.y, 0.4f }, { 0.02f, 0.05f }, m_Bullet.Rotation, m_BulletTexture);
	else
		Engine::Renderer2D::DrawRotatedQuad({ m_Bullet.Position.x, m_Bullet.Position.y, 0.4f }, { 0.0f, 0.0f }, m_Bullet.Rotation, m_BulletTexture);

	for (auto& box : m_Boxes)
	{
		Engine::Renderer2D::DrawQuad({ box.Position.x, box.Position.y, 0.5f }, { box.Size.x, box.Size.y }, box.Color);
	}

	Engine::Renderer2D::EndScene();
}

void Test::Logic(Engine::Timestep ts)
{

	
#endif
	if (Engine::Input::IsKeyPressed(ENGINE_KEY_UP))
	{
		m_TankPosition.y += 0.2f * ts;
		m_TankRotation = 0.0f;
	}
	else if (Engine::Input::IsKeyPressed(ENGINE_KEY_DOWN))
	{
		m_TankPosition.y -= 0.2f * ts;
		m_TankRotation = 180.0f;
	}
	if (Engine::Input::IsKeyPressed(ENGINE_KEY_RIGHT))
	{
		m_TankPosition.x += 0.2 * ts;
		m_TankRotation = -90.0f;
	}
	else if (Engine::Input::IsKeyPressed(ENGINE_KEY_LEFT))
	{
		m_TankPosition.x -= 0.2f * ts;
		m_TankRotation = 90.0f;
	}
	//------------------------------------------------------------------
	if (Engine::Input::IsKeyPressed(ENGINE_KEY_RIGHT) && Engine::Input::IsKeyPressed(ENGINE_KEY_UP))
	{
		m_TankRotation = -45.0f;
	}
	else if (Engine::Input::IsKeyPressed(ENGINE_KEY_LEFT) && Engine::Input::IsKeyPressed(ENGINE_KEY_UP))
	{
		m_TankRotation = 45.0f;
	}

	if (Engine::Input::IsKeyPressed(ENGINE_KEY_RIGHT) && Engine::Input::IsKeyPressed(ENGINE_KEY_DOWN))
	{
		m_TankRotation = -135.0f;
	}
	else if (Engine::Input::IsKeyPressed(ENGINE_KEY_LEFT) && Engine::Input::IsKeyPressed(ENGINE_KEY_DOWN))
	{
		m_TankRotation = 135.0f;
	}

	if (Engine::Input::IsKeyPressed(ENGINE_KEY_SPACE))
	{
		Bullet bullet;

		if (m_TankRotation == 0.0f)
		{
			bullet.Direction = { 0.0f, 1.0f };
			bullet.Position = { m_TankPosition.x, m_TankPosition.y + 0.15 };
		}

		else if (m_TankRotation == 45.0f)
		{
			bullet.Direction = { -1.0f, 1.0f };
			bullet.Position = { m_TankPosition.x - 0.15, m_TankPosition.y + 0.15f };
		}

		else if (m_TankRotation == 90.0f)
		{
			bullet.Direction = { -1.0f, 0.0f };
			bullet.Position = { m_TankPosition.x - 0.15, m_TankPosition.y };
		}

		else if (m_TankRotation == 135.0f)
		{
			bullet.Direction = { -1.0f, -1.0f };
			bullet.Position = { m_TankPosition.x - 0.15, m_TankPosition.y - 0.15f };
		}

		else if (m_TankRotation == 180.0f)
		{
			bullet.Direction = { 0.0f, -1.0f };
			bullet.Position = { m_TankPosition.x, m_TankPosition.y  - 0.15};
		}

		else if (m_TankRotation == -45.0f)
		{
			bullet.Direction = { 1.0f, 1.0f };
			bullet.Position = { m_TankPosition.x + 0.15, m_TankPosition.y + 0.15f };
		}

		else if (m_TankRotation == -90.0f)
		{
			bullet.Direction = { 1.0f, 0.0f };
			bullet.Position = { m_TankPosition.x + 0.15, m_TankPosition.y };
		}

		else if (m_TankRotation == -135.0f)
		{
			bullet.Direction = { 1.0f, -1.0f };
			bullet.Position = { m_TankPosition.x + 0.15, m_TankPosition.y - 0.15f };
		}

		bullet.Rotation = m_TankRotation;
		bullet.Speed = 1.0f;
		bullet.Life = 1.0f;

		if(m_Bullet.Life <= 0.0f)
			m_Bullet = bullet;
	}
	if (m_Bullet.Life >= 0.0f)
	{
		m_Bullet.Position += (m_Bullet.Speed * ts) * m_Bullet.Direction;
		m_Bullet.Life -= ts;
	}

	for (auto& box : m_Boxes)
	{
		if (ChechCollision(m_TankPosition.x, m_TankPosition.y, 0.2f, 0.2f, box.Position.x, box.Position.y, box.Size.x, box.Size.y))
			std::cout << "Collision detection!" << std::endl;
	}
}

void Test::Clear()
{

	
#endif
	Engine::RenderCommand::Clear();
}

bool Test::ChechCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{

	
#endif
	return (((x1 + w1) > (x2)) || ((x2 + w2) > x1) || ((y1 + h1) > (y2)) || ((y2 + h2) > y1));
}
