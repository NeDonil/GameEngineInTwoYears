#pragma once
#include "Engine.h"
#include <vector>

namespace Engine
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		OrthographicCameraController m_CameraController;

		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;

		Entity m_SquareEntity;

		Ref<Texture2D> m_CheckerboardTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize;
		glm::vec4 m_SquareColor = { 0.8f, 0.3f, 0.2f, 1.0f };

		struct ProfileResult {
			const char* Name;
			float Time;
		};

	};
}