#pragma once

#include <Engine.h>

struct Bullet
{
	glm::vec2 Position;
	glm::vec2 Direction;
	float Rotation;
	float Speed;
	float Life = 0.0f;
};

struct Box
{
	Box(glm::vec2 position, glm::vec2 size, glm::vec4 color)
	{
		this->Position = position;
		this->Size = size;
		this->Color = color;
	}

	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;
};

class Test : public Engine::Layer
{
public:
	Test();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Engine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Engine::Event& event) override;

	void Render();
	void Logic(Engine::Timestep ts);
	void Clear();

	inline void AddBox(Box& box) { m_Boxes.push_back(box); }
	bool ChechCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

private:
	Engine::OrthographicCameraController m_CameraController;

	Engine::Ref<Engine::Shader> m_Shader;

	glm::vec2 m_TankPosition = {0.0f, 0.0f};
	float m_TankRotation = 0;

	Engine::Ref<Engine::Texture2D> m_TankTexture;
	Engine::Ref<Engine::Texture2D> m_BulletTexture;
	Engine::Ref<Engine::Texture2D> m_CheckerboardTexture;

	Bullet m_Bullet;

	std::vector<Box> m_Boxes;
};