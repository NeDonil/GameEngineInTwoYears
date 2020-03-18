#pragma once
#include "Engine.h"
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

	glm::vec4 m_SquareColor = { 0.8f, 0.3f, 0.2f, 1.0f};

	glm::vec4 m_RedColor    = { 1.0f,  0.0f,  0.0f,  1.0f };
	glm::vec4 m_OrangeColor = { 1.0f,  0.65f, 0.0f,  1.0f };
	glm::vec4 m_YellowColor = { 1.0f,  1.0f,  0.0f,  1.0f };
	glm::vec4 m_GreenColor  = { 0.0f,  1.0f,  0.0f,  1.0f };
	glm::vec4 m_BlueColor   = { 0.0f,  0.0f,  1.0f,  1.0f };
	glm::vec4 m_PurpleColor = { 0.5f,  0.0f,  0.5f,  1.0f };

	struct ProfileResult {
		const char* Name;
		float Time;
	};

};