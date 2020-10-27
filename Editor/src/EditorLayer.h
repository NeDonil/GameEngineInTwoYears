#pragma once
#include "Engine.h"
#include <vector>
#include <glm/glm.hpp>
#include "Panels/SceneHierarchyPanel.h"

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
		Ref<SceneHierarchyPanel> m_Panel;

		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;

		Entity m_OrangeSquareEntity;
		Entity m_BlueSquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize;
		glm::vec4 m_SquareColor = { 0.8f, 0.3f, 0.2f, 1.0f };

		struct ProfileResult {
			const char* Name;
			float Time;
		};

	};
}