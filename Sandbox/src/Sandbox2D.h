#pragma once
#include "Engine.h"
#include "Engine/Renderer/Animation2D.h"
#include <vector>

class Sandbox2D : public Engine::Layer
{
public:
	Sandbox2D();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Engine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Engine::Event& event) override;
private:
	Engine::OrthographicCameraController m_CameraController;

	Engine::Ref<Engine::Shader> m_Shader;

	Engine::Ref<Engine::VertexArray> m_SquareVA;

	Engine::Ref<Engine::Texture2D> m_Texture;
	Engine::Ref<Engine::Texture2D> m_CheckerboardTexture;
	Engine::Ref<Engine::Texture2D> m_SpritesheetTexture;
	Engine::Ref<Engine::Texture2D> m_GirlsheetTexture;

	Engine::Ref<Engine::SubTexture2D> m_SpriteStairs;
	Engine::Ref<Engine::SubTexture2D> m_SpriteTree;

	Engine::Ref<Engine::Animation2D> m_Animation;

	glm::vec4 m_SquareColor = { 0.8f, 0.3f, 0.2f, 1.0f};

	struct ProfileResult {
		const char* Name;
		float Time;
	};

};